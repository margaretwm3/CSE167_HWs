#include <iostream>

#include <GLUT/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "cube.h"
#include <Math.h>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <vector>
#define PI 3.14159265f

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int Window::spin_direction =  1.0;  // set spin_direction default to be clockwise
bool ball_mode = false;     //default is the cube
bool house = false;
bool bunny = false;
bool dragon = false;

float acc= 0.01;
float x_acc = 0.002;
float ballRadius = 2.0f;
float ballXMax,ballXMin,ballYMax,ballYMin; //calculate the boundary
float xSpeed = 0.15f; //Ball's speed in x,y directions
float ySpeed = 0.00f;

//call the camera set function to set e,d,up
Vector3 *e;
Vector3 *d;
Vector3 *up;

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

//calculate the center of the model
double center_x, center_y,center_z;

// This data structure defines a simple house

int nVerts = 42;    // your vertex array needs to have this many entries

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

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
    1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
    0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
    1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
    0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
    0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
    0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
    
    0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
    0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
    1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
    0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
    0,0,1, 0,0,1, 0,0,1,};              // rear attic wall is red

// The index data stores the connectivity of the triangles;
// index 0 refers to the first triangle defined above
int indices[] = {
    0,2,3,    0,1,2,      // front face
    4,6,7,    4,5,6,      // left face
    8,10,11,  8,9,10,     // back face
    12,14,15, 12,13,14,   // right face
    16,18,19, 16,17,18,   // top face
    20,22,23, 20,21,22,   // bottom face
    
    24,26,27, 24,25,26,   // grass
    28,29,30,             // front attic wall
    31,33,34, 31,32,33,   // left slope
    35,37,38, 35,36,37,   // right slope
    39,40,41};            // rear attic wall

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
    
    if(!ball_mode && house == false){
        Globals::cube.spin(spin_direction);  // rotate cube; if it spins too fast try smaller values and vice versa
        displayCallback();
    }
    else if (ball_mode == true && house == false && bunny == false && dragon == false){
        ySpeed += acc;
        Globals::ball.fall(ySpeed);//make the ball bounce
        Globals::ball.moveX(xSpeed);
        
        if(Globals::ball.getY() >= ballYMax){
            ySpeed = 0;
        }
        
        else if(Globals::ball.getY() <= ballYMin){
            Globals::ball.fall(-ySpeed);
            ySpeed = -ySpeed + 0.01;
        }
        
        if(Globals::ball.getX() >= ballXMax){
            Globals::ball.moveX(-xSpeed);
            xSpeed = -xSpeed;
        }
        else if(Globals::ball.getX() <= ballXMin){
            Globals::ball.moveX(-xSpeed);
            xSpeed = -xSpeed;
        }
      
      }
      displayCallback(); //called when window redraw is needed
    }// call display routine to show the cube


void Window::houseidleCallback(){
    
}


//idlecallback for bunny
void Window::bunnyidleCallback(){
    if(bunny == true){
        Globals::bunny.spin(1.0);
        displayCallback();
    }
}

//idlecallback for dragon
void Window::dragonidleCallback(){
    if(dragon == true){
        Globals::dragon.spin(1.0);
        displayCallback();
    }
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
 
    if(!ball_mode){
        cerr << "Window::reshapeCallback called" << endl;
        width = w;
        height = h;
        glViewport(0, 0, w, h);  // set new viewport size
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
        glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
        glMatrixMode(GL_MODELVIEW);
    }
    else{
        width = w;
        height = h;
        glViewport(0, 0,w,h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, double(width)/double(height), 1.0, 1000.0);
        glTranslatef(0,0,-20);
        glMatrixMode(GL_MODELVIEW);
    }
    ballYMax = 0 + tan(30 * PI/ 180.0) * 20 - ballRadius;
    ballYMin = 0 - tan(30 * PI/ 180.0) * 20 + ballRadius; // why addition
    ySpeed = 0;
    
    ballXMin = float(width)/height * (0- tan(30 * PI/180) * 20) + ballRadius;
    ballXMax = float(width)/height * (0+ tan(30 * PI/180) * 20) - ballRadius;
}

void Window::processSpecialKeys(int key, int x, int y){
    // display the cube
    if(key == GLUT_KEY_F1)
    {
        ball_mode = false;
        house = false;
        bunny = false;
        dragon = false;
        glutIdleFunc(Window::idleCallback);
        displayCallback();
    }
    //display the house
    else if(key == GLUT_KEY_F2){
        ball_mode = false;
        house = true;
        bunny = false;
        dragon = false;
        e = new Vector3(0,10,10);
        d = new Vector3(0,0,0);
        up = new Vector3(0,1,0);
        //the order passed should be e,d,up
        Globals::camera.set(*e, *d, *up);
        glutIdleFunc(Window::houseidleCallback);
        displayCallback();
    }
    else if(key == GLUT_KEY_F3){
        ball_mode = false;
        house = true;
        e = new Vector3(-15,5,10);
        d = new Vector3(-5,0,0);
        up = new Vector3(0,1,0.5);
        //the order passed should be e,d,up
        Globals::camera.set(*e, *d, *up);
        glutIdleFunc(Window::houseidleCallback);
        displayCallback();
    }
    // Draw the bunny
    else if(key == GLUT_KEY_F4){
        normal.clear();
        position.clear();
        ball_mode = false;
        house = false;
        bunny = true;
        glutIdleFunc(Window::bunnyidleCallback);
        double x;
        double y;
        double z;
        double norX;
        double norY;
        double norZ;
        //read in file
        FILE* file;
        file = fopen("/Users/mingshanwang/Dropbox/CSE167/CSE167HW1/bunny.xyz","r");
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
        //normalize all the normals in the normal vector
        for(int i = 0 ;i < normal.size();i++){
            normal[i].normalize();
        }
        for(int i = 0; i< position.size();i++){
            if(position[i].x < x_smallest){
                x_smallest = position[i].x;
            }
            if(position[i].x>x_biggest){
                x_biggest = position[i].x;
            }
        }
        for(int i = 0; i< position.size();i++){
            if(position[i].y < y_smallest){
                y_smallest = position[i].y;
            }
            if(position[i].y>y_biggest){
                y_biggest = position[i].y;
            }
        }

        for(int i = 0; i< position.size();i++){
            if(position[i].z < z_smallest){
                z_smallest = position[i].z;
            }
            if(position[i].z>z_biggest){
                z_biggest = position[i].z;
            }
        }
        
        cout << "x_smallest is " << x_smallest << endl;
        cout << "y_smallest is " << y_smallest << endl;
        cout << "z_smallest is " << z_smallest << endl;
        cout << "x_biggest is " << x_biggest << endl;
        cout << "y_biggest is " << y_biggest << endl;
        cout << "z_biggest is " << z_biggest << endl;
        center_x = 0.5*(x_smallest + x_biggest);
        center_y = 0.5*(y_smallest + y_biggest);
        center_z = 0.5*(z_smallest + z_biggest);
        displayCallback();
    }
    //Draw the dragon
    else if(key == GLUT_KEY_F5){
        //clear the vector first
        normal.clear();
        position.clear();
        ball_mode = false;
        house = false;
        bunny = false;
        dragon = true;
        glutIdleFunc(Window::dragonidleCallback);
        double x;
        double y;
        double z;
        double norX;
        double norY;
        double norZ;
        //read in file
        FILE* file;
        file = fopen("/Users/mingshanwang/Dropbox/CSE167/CSE167HW1/dragon.xyz","r");
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
        //normalize all the normals in the normal vector
        for(int i = 0 ;i < normal.size();i++){
            normal[i].normalize();
        }
        
        for(int i = 0; i< position.size();i++){
            if(position[i].x < x_smallest){
                x_smallest = position[i].x;
            }
            if(position[i].x>x_biggest){
                x_biggest = position[i].x;
            }
        }
        for(int i = 0; i< position.size();i++){
            if(position[i].y < y_smallest){
                y_smallest = position[i].y;
            }
            if(position[i].y>y_biggest){
                y_biggest = position[i].y;
            }
        }
        
        for(int i = 0; i< position.size();i++){
            if(position[i].z < z_smallest){
                z_smallest = position[i].z;
            }
            if(position[i].z>z_biggest){
                z_biggest = position[i].z;
            }
        }
        cout << "x_smallest is " << x_smallest << endl;
        cout << "y_smallest is " << y_smallest << endl;
        cout << "z_smallest is " << z_smallest << endl;
        cout << "x_biggest is " << x_biggest << endl;
        cout << "y_biggest is " << y_biggest << endl;
        cout << "z_biggest is " << z_biggest << endl;
        center_x = 0.5*(x_smallest + x_biggest);
        center_y = 0.5*(y_smallest + y_biggest);
        center_z = 0.5*(z_smallest + z_biggest);
        
        displayCallback();
    }
}


void Window::processNormalKeys(unsigned char key, int x, int y){
    if(key == 27)
        exit(0);
    
    //toggle the direction of the spin between clockwise and counterclockwise
    else if(key == 't'){
        spin_direction *= -1.0;
    }
    // move cube left by a small amount
    else if(key == 'x'){
        Globals::cube.moveLeft();
        displayCallback();
    }
    // move the cube right by a small amount
    else if (key == 'X'){
        Globals::cube.moveRight();
        displayCallback();
    }
    // move the cube down by a small amount
    else if (key == 'y'){
        Globals::cube.moveDown();
        displayCallback();
    }
    // move the cube up by a small amount
    else if (key == 'Y'){
        Globals::cube.moveUp();
        displayCallback();
    }
    // move the cube zzinto the screen by a small amount
    else if(key == 'z'){
        Globals::cube.moveInto();
        displayCallback();
    }
    // move the cube out of the screen by a small amount
    else if(key == 'Z'){
        Globals::cube.moveOutOf();
        displayCallback();
    }
    //reset cube position, orientation, size and color
    else if(key == 'r'){
        Globals::cube.reset();
        spin_direction = 1.0;
        glColor3f(1.0,1.0,1.0);
        displayCallback();
    }
    
    //o'/'O': orbit cube about the OpenGL window's z axis by a small number of degrees (e.g., 10) per key press, counterclockwise ('o') or clockwise ('O'). The z axis crosses the screen in the center of the OpenGL window. This rotation should not affect the spin other than that it will rotate the spin axis with the cube.
    // counterclockwise
    else if(key == 'o'){
        Globals::cube.orbit(-1);
        displayCallback();
    }
    // clockwise
    else if (key == 'O'){
        Globals::cube.orbit(1);
        displayCallback();
    }
    //scale cube down
    else if(key == 's'){
        if(!ball_mode && dragon == false && bunny == false){
            Globals::cube.scale(0.9);
        }
        else if (bunny == true && dragon == false && ball_mode == false)
            Globals::bunny.scale(0.9);
        else
            Globals::dragon.scale(0.9);
        
        displayCallback();
    }
    // scale cueb up
    else if(key == 'S'){
        if(!ball_mode && dragon == false && bunny == false){
            Globals::cube.scale(1.1);
        }
        else if (bunny == true && dragon == false && ball_mode == false)
            Globals::bunny.scale(1.1);
        else
            Globals::dragon.scale(1.1);
        displayCallback();
    }
    //switch between the ball and the cube
    else if(key == 'b'){
        ball_mode = !ball_mode;
        displayCallback();
    }
    
    //With every key press, display the new cube position with your Vector3 print method in the text window
    Globals::cube.position->dehomogenize();
    // Translate the Vector4 to Vector3
    double vec3_x = Globals::cube.position->x;
    double vec3_y = Globals::cube.position->y;
    double vec3_z = Globals::cube.position->z;
    Vector3 vec3 = Vector3(vec3_x,vec3_y,vec3_z);
    vec3.print("postion vector: ");
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Draw the ball
    if(ball_mode && house == false){
        
        glColor3f(0.5,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
        glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
        // Tell OpenGL what ModelView matrix to use:
        Matrix4 glmatrix;
        glmatrix = Globals::ball.getMatrix();
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        glutSolidSphere(2.5,20.0,20.0);
        glFlush();
        glutSwapBuffers();
 }
    //Draw the house
    else if(house)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
        glMatrixMode(GL_MODELVIEW);
        Matrix4 glmatrix;
        // already inverse of the camera matrix
        glmatrix = Globals::camera.getCameraMatrix();
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        glBegin(GL_TRIANGLES);
        
        int index = -1;
        int length = sizeof(indices)/sizeof(*indices);
        
        //traverse the indices array
        for(int i = 0; i<length;i++){
            index = indices[i];
            index = index * 3;
            glColor3f(colors[index], colors[index+1], colors[index+2]);
            glVertex3f(vertices[index], vertices[index+1], vertices[index+2]);
            //pass vertex to OpenGL
        }
        
        glEnd();
        glFlush();
        glutSwapBuffers();
        
    }
    //Draw the bunny
    else if(bunny == true){
        glMatrixMode(GL_MODELVIEW);
        Matrix4 glmatrix;
        glmatrix = Globals::bunny.getMatrix();
        double aspectRatio = (double)width/height;
        
        //make a scaling matrix for bunny based on the window height and width
        Matrix4 scalingMatrix = Matrix4();
        scalingMatrix.identity();
        double x_ratio = (2*(tan(30 * PI/ 180.0) * 20) * aspectRatio)/(x_biggest -x_smallest);
        cout << "width " << width << endl;
        cout << "height " << height << endl;
        cout << "minus " << x_biggest-x_smallest << endl;
        double y_ratio = 2*(tan(30 * PI/ 180.0) * 20)/(y_biggest - y_smallest);
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
        cout << "x : " << x_ratio << endl;
        cout << "y : " << y_ratio << endl;
        cout << "z:  " << z_ratio << endl;
        cout << "scaling : " << scaling << endl;
        scalingMatrix.makeScale(scaling, scaling,scaling);
        scalingMatrix.print("scaling matrix is ");
        
        Matrix4 translation = Matrix4();
        translation.identity();
        translation.makeTranslate(-center_x, -center_y, -center_z);
        translation.print("translation matrix :");
        
        //translation.print("translation matrix: ");
        glmatrix = glmatrix * scalingMatrix;
        glmatrix = glmatrix * translation;
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        
        for (int i = 0;i < normal.size();i++)
        {
            glPointSize(10);
            glBegin(GL_POINTS);
            glColor3f(normal[i].x, normal[i].y, normal[i].z);
            glNormal3d(normal[i].x, normal[i].y, normal[i].z);
            glVertex3d(position[i].x, position[i].y, position[i].z);
            glEnd();
        }
        glFlush();
        glutSwapBuffers();
    }
    else if(dragon == true){
        glMatrixMode(GL_MODELVIEW);
        Matrix4 glmatrix;
        glmatrix = Globals::dragon.getMatrix();
        //make a scaling matrix for bunny based on the window height and width
        
        double aspectRatio = (double)width/height;
        Matrix4 scalingMatrix = Matrix4();
        scalingMatrix.identity();
        double x_ratio = (2*(tan(30 * PI/ 180.0) * 20) * aspectRatio)/(x_biggest -x_smallest);
        cout << "width " << width << endl;
        cout << "height " << height << endl;
        cout << "minus " << x_biggest-x_smallest << endl;
        double y_ratio = 2*(tan(30 * PI/ 180.0) * 20)/(y_biggest - y_smallest);
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
        cout << "x : " << x_ratio << endl;
        cout << "y : " << y_ratio << endl;
        cout << "z:  " << z_ratio << endl;
        cout << "scaling : " << scaling << endl;
        scalingMatrix.makeScale(scaling, scaling,scaling);
        Matrix4 translation = Matrix4();
        translation.identity();
        translation.makeTranslate(-center_x, -center_y, -center_z);
        //translation.print("translation matrix: ");
        glmatrix = glmatrix * scalingMatrix;
        glmatrix = glmatrix * translation;
        
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        
        for (int i = 0;i < normal.size();i++)
        {
            glPointSize(10);
            glBegin(GL_POINTS);
            glColor3f(normal[i].x, normal[i].y, normal[i].z);
            glNormal3d(normal[i].x, normal[i].y, normal[i].z);
            glVertex3d(position[i].x, position[i].y, position[i].z);
            glEnd();

        }
        glFlush();
        glutSwapBuffers();
    }
    // Draw the cube
    else if(!ball_mode && house == false){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        Matrix4 glmatrix;
        glmatrix = Globals::cube.getMatrix();
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());

        // Draw all six faces of the cube:
        glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue.
                                // To change the color of the other faces you will need to repeat this call before each face is drawn.
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);   
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
  
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
   
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f(-5.0,  5.0, -5.0);
  
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
  
    glEnd();
    glFlush();
    glutSwapBuffers();
  }

}
