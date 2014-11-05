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
#include <math.h>
#include <OPENGL/gl.h>
#include <GLUT/glut.h>
using namespace std;

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];

using namespace std;

struct Color    // generic color class
{
    float r,g,b;  // red, green, blue
};

// These are the x,y,z coordinates of the vertices of the triangles
float vertices[] = {
    -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
    -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
    4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
    4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
    4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
    -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face
    
    -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
    -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
    4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
    -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
    4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall


void loadData()
{
    // point cloud parser goes here
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
}

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b)
{
   int offset = y*window_width*3 + x*3;
    pixels[offset]   = r;
    pixels[offset+1] = g;
    pixels[offset+2] = b;
}

void rasterize()
{
    // Put your main rasterization loop here
    // It should go over the point model and call drawPoint for every point in it
    Matrix4 modelViewMatrix = Matrix4();
    modelViewMatrix.identity();
    
    //create the camera matrix
    Camera cameraMatrix = Camera();
    Vector3 *e = new Vector3(0,10,10);
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
    
    for(int i = 0;i<sizeof(vertices); i+=3){
        Vector4 p = Vector4(vertices[i],vertices[i+1],vertices[i+2],1);
        p = modelViewMatrix *p;
        p = camMatrix* p;
        p = projectionMatrix *p;
        //dehomogenize the vector4
        p.dehomogenize();
        if(p.getX() < -1 || p.getX() >1 || p.getY() <-1 || p.getY() >1){
            continue;
        }
        p = viewport * p;
        drawPoint(p.getX(), p.getY(), 1, 1, 1);
    }
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
    window_width  = new_width;
    window_height = new_height;
    delete[] pixels;
    pixels = new float[window_width * window_height * 3];
    displayCallback();
}

void keyboardCallback(unsigned char key, int, int)
{
    if(key == 27){
        exit(0);
    }
    cerr << "Key pressed: " << key << endl;
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
    
    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
    glutMainLoop();
}
