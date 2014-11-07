//
//  Rasterizer.cpp
//  CSE167HW3
//
//  Created by Mingshan Wang on 11/4/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Rasterizer.h"
#include "Camera.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <OPENGL/gl.h>
#include <GLUT/glut.h>
using namespace std;

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];//frame buffer
bool bunny = true;
bool dragon = false;
double angle;
//calculate the center of the model
double center_x, center_y,center_z;
bool spin;
Matrix4 modelViewMatrix = Matrix4();

//for bunny and dragon
vector<Vector3> normal;
vector<Vector3> position;
//Calculate the minimum and maximum point coordinates in all three dimensions, one for each dimension (x,y,z), store the smallest and biggest that come across and display
double x_smallest = 100;
double x_biggest = 0;
double y_smallest = 100;
double y_biggest = 0;
double z_smallest = 100;
double z_biggest = 0;

//for shading
Vector3 lightSource = Vector3(1.5,1.5,1.5);
double brightness = 1000;

struct Color    // generic color class
{
    float r,g,b;  // red, green, blue
};

Color lightColor = {1.0,1.0,1.0};
bool illumination = false;

//Create a zbuffer
static float* zbuffer  = new float[window_width * window_height];//map to each pixel
bool zbufferOn = false;

//Resize the point size
bool  pointReSize= false;


void loadData()
{
    // point cloud parser goes here
    double x;
    double y;
    double z;
    double norX;
    double norY;
    double norZ;
    
    x_smallest = 100;
    x_biggest = 0;
    y_smallest = 100;
    y_biggest = 0;
    z_smallest = 100;
    z_biggest = 0;
    
    if(bunny == true && dragon == false){
        normal.clear();
        position.clear();
        //read in file
        FILE* file;
        file = fopen("/Users/Margaret/Desktop/CSE167_HWs/CSE167HW1/bunny.xyz","r");
        while(!feof(file)){
            fscanf(file,"%lf",&x);
            fscanf(file,"%lf",&y);
            fscanf(file,"%lf",&z);
            fscanf(file,"%lf",&norX);
            fscanf(file,"%lf",&norY);
            fscanf(file, "%lf",&norZ);
            Vector3 p = Vector3(x, y, z);
            Vector3 n = Vector3(norX, norY, norZ);
            normal.push_back(n);
            position.push_back(p);
       }
    }
    else if(dragon == true && bunny == false){
        normal.clear();
        position.clear();
        //read in file
        FILE* file;
        file = fopen("/Users/Margaret/Desktop/CSE167_HWs/CSE167HW1/dragon.xyz","r");
        while(!feof(file)){
            fscanf(file,"%lf",&x);
            fscanf(file,"%lf",&y);
            fscanf(file,"%lf",&z);
            fscanf(file,"%lf",&norX);
            fscanf(file,"%lf",&norY);
            fscanf(file, "%lf",&norZ);
            Vector3 p = Vector3(x, y, z);
            Vector3 n = Vector3(norX, norY, norZ);
            normal.push_back(n);
            position.push_back(p);
        }
    }
    
    //normalize all the normals in the normal vector
    for(int i = 0 ;i < normal.size();i++){
        normal[i].normalize();
    }
    
    for(int i = 0; i< position.size();i++){
        if(position[i].getX()< x_smallest){
            x_smallest = position[i].getX();
        }
        if(position[i].getX()>x_biggest){
            x_biggest = position[i].getX();
        }
    }
    
    for(int i = 0; i< position.size();i++){
        if(position[i].getY() < y_smallest){
            y_smallest = position[i].getY();
        }
        if(position[i].getY()>y_biggest){
            y_biggest = position[i].getY();
        }
    }
    
    for(int i = 0; i< position.size();i++){
        if(position[i].getZ() < z_smallest){
            z_smallest = position[i].getZ();
        }
        if(position[i].getZ()>z_biggest){
            z_biggest = position[i].getZ();
        }
    }
    
    center_x = 0.5*(x_smallest + x_biggest);
    center_y = 0.5*(y_smallest + y_biggest);
    center_z = 0.5*(z_smallest + z_biggest);
}

// Clear frame buffer
void clearBuffer()
{
    Color clearColor = {0.0, 0.0, 0.0};   // clear color: black
    for (int i=0; i<window_width*window_height; ++i)
    {
        pixels[i*3]   = clearColor.r;
        pixels[i*3+1] = clearColor.g;
        pixels[i*3+2] = clearColor.b;
    }
    //clear the zbuffer
    for(int i =0;i< window_width * window_height;i++){
        zbuffer[i] = 1;
    }
}

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b,int pointSize)
{
    int offset = 0;
    //draw horizontally
    for(int i = 0;i<pointSize;i++){
        //draw vertically
        for(int j = 0;j<pointSize;j++){
            offset = (x+i)*3 + (j+y)*window_width*3;
            if(offset > window_width * window_height * 3)
                continue;
            pixels[offset] =r;
            pixels[offset +1] =g;
            pixels[offset +2]=b;
        }
    }
}

void rasterize()
{
    // Put your main rasterization loop here
    // It should go over the point model and call drawPoint for every point in it
    //create the camera matrix
    Camera cameraMatrix = Camera();
    Vector3 *e = new Vector3(0,0,20);
    Vector3 *d = new Vector3(0,0,0);
    Vector3 *up =new Vector3(0,1,0);
    cameraMatrix.set(*e,*d,*up);
    Matrix4 camMatrix = cameraMatrix.getCameraMatrix();//get the inverse of the camera matrix
    //create projection matrix
    Matrix4 projectionMatrix;
    double aspectRatio = (double)window_width/window_height;
    projectionMatrix.makeProjectionMatrix(60, aspectRatio, 1,1000);
    projectionMatrix.print("projection matrix is ");
    //Create viewpoert matrix
    Matrix4 viewport;
    viewport.makeViewportMatrix(0, window_width, 0, window_height);
    viewport.print("viewport matrix is ");

    //make a scaling matrix for bunny based on the window height and width
    Matrix4 scalingMatrix = Matrix4();
    scalingMatrix.identity();
    double x_ratio = (2*(tan(30 * M_PI/ 180.0) * 20) * aspectRatio)/(x_biggest -x_smallest);
    double y_ratio = 2*(tan(30 * M_PI/ 180.0) * 20)/(y_biggest - y_smallest);
    double z_ratio = 40/(z_biggest - z_smallest);
    double scaling=1000;

    if(x_ratio < y_ratio){
        scaling = x_ratio;
    }
    else
        scaling = y_ratio;
    if(z_ratio < scaling){
        scaling = z_ratio;
    }
    scalingMatrix.makeScale(scaling, scaling,scaling);
    Matrix4 translation = Matrix4();
    translation.identity();
    translation.makeTranslate(-center_x, -center_y,-center_z);
    int skipCount = 0;
    //for(int i = 0;i<sizeof(vertices); i+=3){
    for(int i = 0;i<position.size();i++){
        double red = 1, green = 1, blue = 1;
        Vector4 p = Vector4(position[i].getX(),position[i].getY(),position[i].getZ(),1);
        //illumination
        Vector3 norm = Vector3(normal[i].getX(),normal[i].getY(),normal[i].getZ());
        if(illumination == true){
            lightSource.normalize(); norm.normalize();
            red = lightSource.dot(lightSource, norm)/((norm-lightSource).length()*(norm-lightSource).length()*M_PI) * brightness * lightColor.r * 1;
            green = lightSource.dot(lightSource, norm)/((norm-lightSource).length()*(norm-lightSource).length()*M_PI) * brightness * lightColor.g * 0;
            blue = lightSource.dot(lightSource, norm)/((norm-lightSource).length()*(norm-lightSource).length()*M_PI) * brightness * lightColor.b * 0;
        }
        p = modelViewMatrix *p;
        p = translation * p;
        p = scalingMatrix * p;
        p = camMatrix * p;
        p = projectionMatrix *p;
        //dehomogenize the vector4
        p.dehomogenize();
        if(p.getX() < -1 || p.getX() >1 || p.getY() <-1 || p.getY() >1){
            continue;
        }
        //calculate the zbuffer values
        if(zbufferOn == true){
            //store the z-value before the viewport
            double tmp = p.getZ();
            p = viewport * p;
            int index = p.getX() + p.getY() * window_width;
            if(index >= window_width * window_height || index < 0){
                continue;
            }
            if(zbuffer[index] > tmp){
                //update the zbuffer value
                zbuffer[index] = tmp;
                if(pointReSize == true){
                    if(tmp<0.84){
                        drawPoint(p.getX(), p.getY(), red, green, blue,4);
                    }
                    else if(tmp < 0.87){
                        drawPoint(p.getX(), p.getY(), red, green, blue,2);
                    }
                    else{
                        drawPoint(p.getX(), p.getY(), red, green, blue,1);
                    }
               }
                drawPoint(p.getX(), p.getY(),red, green, blue,1);
            }
            else{
                skipCount++;
            }
        }
        else{
            p = viewport * p;
            drawPoint(p.getX(), p.getY(), red, green, blue,2);
        }
    }
    cout << "skipCount is " << skipCount << endl;

}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
    window_width  = new_width;
    window_height = new_height;
    delete[] pixels;
    delete[] zbuffer;
    pixels = new float[window_width * window_height * 3];
    zbuffer = new float[window_width * window_height];
    displayCallback();
}

void keyboardCallback(unsigned char key, int, int)
{
    if(key == 27){
        exit(0);
    }
    //scale bunny or dragon down
    else if(key == 's'){
        Matrix4 tmp = Matrix4();
        //tmp.identity();
        tmp.makeScale(0.9,0.9,0.9);
        // the order is important to keep in the local space
        modelViewMatrix =  modelViewMatrix * tmp;
        displayCallback();
    }
    // scale cueb up
    else if(key == 'S'){
        Matrix4 tmp = Matrix4();
        //tmp.identity();
        tmp.makeScale(1.1,1.1,1.1);
        // the order is important to keep in the local space
        modelViewMatrix = modelViewMatrix * tmp;
        displayCallback();
    }
    //make object rotate
    else if(key == 'r'){
        Matrix4 tmp = Matrix4();
        tmp.identity();
        tmp.makeRotateY(2.0);
        modelViewMatrix = modelViewMatrix * tmp;
        displayCallback();
    }
    //without illumination, white
    else if(key == '1'){
        illumination = false;
        displayCallback();
    }
    //with illumination shading
    else if (key == '2'){
        illumination = true;
        displayCallback();
    }
    //turn on the zbuffer
    if(key == '3'){
        zbufferOn = true;
        displayCallback();
    }
    //specify the point size
    if(key == '4'){
        pointReSize = true;
        displayCallback();
    }
    cerr << "Key pressed: " << key << endl;
}

void processSpecialKeys(int key, int x, int y){
    modelViewMatrix.identity();
    //display the bunny
    if(key == GLUT_KEY_F1)
    {
        bunny = true;
        dragon = false;
        loadData();
        displayCallback();
       
    }
    //display the dragon
    else if(key == GLUT_KEY_F2){
        dragon = true;
        bunny = false;
        loadData();
        displayCallback();
    }
}

void idleCallback(){
    displayCallback();
}

void displayCallback()
{
    clearBuffer();
    rasterize();
    // glDrawPixels writes a block of pixels to the framebuffer
    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Rasterizer");
    loadData();
    modelViewMatrix.identity();
    
    //initialize the zbuffer
    double zbufferSize = window_width * window_height;
    for(int i  = 0; i< zbufferSize ;i++){
        zbuffer[i] = 1;
    }
    
    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutIdleFunc(idleCallback);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(keyboardCallback);
    glutMainLoop();
}
