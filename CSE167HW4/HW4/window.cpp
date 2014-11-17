#include <iostream>

#include <GLUT/glut.h>

#include "Window.h"
#include "main.h"
#include "MatrixTransform.h"
#include "Robot.h"
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

double forwardAngle = -28;
double backwardAngle = 28;
bool re = false;
bool displayArmy = false;

//call the camera set function to set e,d,up
Vector3 *e;
Vector3 *d;
Vector3 *up;

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
    displayCallback(); //called when window redraw is needed
}// call display routine to show the cube


//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback(){
    cerr << "Window::displayCallback called" << endl;
    glColor3f(0.5,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);
    Matrix4 glmatrix;
    glmatrix.identity();
    e = new Vector3(0,3,10);
    d = new Vector3(0,0,0);
    up = new Vector3(0,1,0);
    Globals::camera.set(*e, *d, *up);
    // already inverse of the camera matrix
    glmatrix = Globals::camera.getCameraMatrix();
    //do not need to do transpose of camera matrix here
    glLoadMatrixd(glmatrix.getPointer());
    if(re == false){
        forwardAngle++;
        backwardAngle--;
    }
    else{
        forwardAngle--;
        backwardAngle++;
    }
    if(forwardAngle == 28){
        re = !re;
    }else if(forwardAngle == -28){
        re = !re;
    }
    if(!displayArmy){
        Globals::robot.buildRobot(forwardAngle, backwardAngle);
        /*Robot robot = Robot();
        robot.buildRobot(forwardAngle,backwardAngle);
        //cout << "num of childs " << world->numOfChild << endl;
        //cout << "forward " << forwardAngle << "backward " << backwardAngle << endl;
        //reset the armAngle to make it like walking
         */
        Globals::robot.root->draw(glmatrix);//pass in the identity matrix to the draw function
        //glmatrix.print("drawboundingbox ");
        Globals::robot.root->drawBoundingBox(glmatrix);
    //display army
    }else{
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                Robot r = Robot();
                r.buildRobot(forwardAngle, backwardAngle);
                r.setLocation(15*i, 2,-10 * j);
                Globals::root.addChild(r.root);
            }
        }
        Globals::root.draw(glmatrix);
        Globals::root.drawBoundingBox(glmatrix);
    }
        glEnd();
        glFlush();
        glutSwapBuffers();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
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



void Window::processNormalKeys(unsigned char key, int x, int y){
    if(key == 27)
        exit(0);
    //turn on/off the bounding box
    else if(key=='b'){
        Globals::boundingBox = ! Globals::boundingBox;
        displayCallback();
    }
    else if(key == 's'){
      Globals::robot.scaling(0.9);
      displayCallback();
    }
    else if(key == 'S'){
      cout << "S is pressed " << endl;
      Globals::robot.scaling(1.1);
      displayCallback();
    }
    //key for army
    else if(key == 'a'){
        displayArmy = !displayArmy;
        displayCallback();
      }
}


