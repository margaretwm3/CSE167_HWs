#include <iostream>

#include <GLUT/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "cube.h"
#include <Math.h>
#include <stdlib.h>
#define PI 3.14159265f

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int Window::spin_direction =  1.0;  // set spin_direction default to be clockwise
bool ball_mode = false;     //default is the cube

float acc= 0.01;
float x_acc = 0.002;
float ballRadius = 2.0f;
float ballXMax,ballXMin,ballYMax,ballYMin; //calculate the boundary
float xSpeed = 0.15f; //Ball's speed in x,y directions
float ySpeed = 0.00f;


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
    if(!ball_mode){
        Globals::cube.spin(spin_direction);  // rotate cube; if it spins too fast try smaller values and vice versa
        displayCallback();
    }
    else{
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
        displayCallback(); //called when window redraw is needed
      
    }// call display routine to show the cube
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
        Globals::cube.scale(0.9);
        displayCallback();
    }
    // scale cueb up
    else if(key == 'S'){
        Globals::cube.scale(1.1);
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
    if(ball_mode){
        glColor3f(0.5,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
        glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
        // Tell OpenGL what ModelView matrix to use:
        Matrix4 glmatrix;
        glmatrix = Globals::ball.getMatrix();
        glmatrix.print("hello");
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        glutSolidSphere(2.5,20.0,20.0);
        glFlush();
        glutSwapBuffers();
 }
// if it is the cube
    else
    {
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
