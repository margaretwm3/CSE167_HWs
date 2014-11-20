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
#include <set>
#include "Material.h"
#define PI 3.14159265f

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int Window::spin_direction =  1.0;  // set spin_direction default to be clockwise

double forwardAngle = -28;
double backwardAngle = 28;
bool re = false;
bool displayArmy = false;

bool bunny = false;
bool dragon = false;
bool bear = false;

//call the camera set function to set e,d,up
Vector3 *e;
Vector3 *d;
Vector3 *up;

vector<Vector3>position;
vector<Vector3>normal;
vector<Vector3>color;

GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//create three seperate light positions
GLfloat light_position[] = { 1.0 , 1.0, 1.0, 1.0 };


int movement; //switch between different states
Vector3 lastPoint = Vector3(0,0,0); // class variable last point
Vector3 lastPoint_z = Vector3(0,0,0);

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
    displayCallback(); //called when window redraw is needed
}// call display routine to show the cube

void Window::idleBunnyCallback(){
    displayBunnyCallback();
}

void Window::idleDragonCallback(){
    displayDragonCallback();
}

void Window::idleBearCallback(){
    displayBearCallback();
}

void Window::displayBunnyCallback(){

    cerr << "displayBunnyCallback called " << endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_LIGHTING);
    glPushMatrix();
        Matrix4 tmp = Matrix4();
    tmp.identity();
    tmp.makeTranslate(Globals::light.position->x, Globals::light.position->y, Globals::light.position->z);
    tmp.transpose();
    glLoadMatrixd(tmp.getPointer());
    glutSolidSphere(0.5,20,20);// for point light
    glPopMatrix();
    
    
    light_position[0] = Globals::light.position->x;
    light_position[1] = Globals::light.position->y;
    light_position[2] = Globals::light.position->z;
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
  
    
    cout << "global light position x "<<Globals::light.position->x<< endl;
    cout << "global light position y "<<Globals::light.position->y << endl;
    cout << "global light position z "<<Globals::light.position->z << endl;
    cout << "light position x "<<light_position[0] << endl;
    cout << "light position y "<<light_position[1] << endl;
    cout << "light position z "<<light_position[2] << endl;
  
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
    GLfloat mat_ambient_color[] = { 0.f, .8f, .8f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient_color);
    
    //lighting model for bunny
    Material bunny = Material(GL_FRONT_AND_BACK);
    //bunny.setColorIndexes(mat_ambient_color);
    bunny.setAmbient(mat_ambient);
    bunny.setDiffuse(mat_diffuse);
    bunny.setSpecular(mat_specular);
    bunny.setShininess(high_shininess);//makes bunny more shiny
    
    Matrix4 glmatrix;
    glmatrix = Globals::bunny.getMatrix();
    double aspectRatio = (double)width/height;
    
    //make a scaling matrix for bunny based on the window height and width
    Matrix4 scalingMatrix = Matrix4();
    scalingMatrix.identity();
    double x_ratio = (2*(tan(30 * PI/ 180.0) * 20) * aspectRatio)/(Globals::bunny.x_biggest -Globals::bunny.x_smallest);
    double y_ratio = 2*(tan(30 * PI/ 180.0) * 20)/(Globals::bunny.y_biggest - Globals::bunny.y_smallest);
    double z_ratio = 40/(Globals::bunny.z_biggest - Globals::bunny.z_smallest);
    double scaling=1000;
    
    if(x_ratio < y_ratio){
        scaling = x_ratio;
    }
    else
        scaling = y_ratio;
    if(z_ratio < scaling){
        scaling = z_ratio;
    }
    
    scalingMatrix.makeScale(0.7*scaling, 0.7*scaling,0.7*scaling);
    
    Matrix4 translation = Matrix4();
    translation.identity();
    translation.makeTranslate(-Globals::bunny.center_x, -Globals::bunny.center_y, -Globals::bunny.center_z);
    translation.print("translation matrix :");
    glmatrix = glmatrix * scalingMatrix;
    glmatrix = glmatrix * translation;
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
   
    
    for (int i = 0;i < Globals::bunny.face_normal.size();i++)
    {
        glBegin(GL_TRIANGLES);
        Vector3 fv = Globals::bunny.face_vertice[i];
        Vector3 fn = Globals::bunny.face_normal[i];
        
        glColor3f(Globals::bunny.color[fv.x-1].x, Globals::bunny.color[fv.x-1].y, Globals::bunny.color[fv.x-1].z);
        glNormal3d(Globals::bunny.normal[fn.x-1].x, Globals::bunny.normal[fn.x-1].y,  Globals::bunny.normal[fn.x-1].z);
        glVertex3d(Globals::bunny.position[fv.x-1].x, Globals::bunny.position[fv.x-1].y, Globals::bunny.position[fv.x-1].z);
        
        glColor3f(Globals::bunny.color[fv.y-1].x, Globals::bunny.color[fv.y-1].y, Globals::bunny.color[fv.y-1].z);
        glNormal3d(Globals::bunny.normal[fn.y-1].x, Globals::bunny.normal[fn.y-1].y,  Globals::bunny.normal[fn.y-1].z);
        glVertex3d(Globals::bunny.position[fv.y-1].x, Globals::bunny.position[fv.y-1].y, Globals::bunny.position[fv.y-1].z);
        
        glColor3f(Globals::bunny.color[fv.z-1].x, Globals::bunny.color[fv.z-1].y, Globals::bunny.color[fv.z-1].z);
        glNormal3d(Globals::bunny.normal[fn.z-1].x, Globals::bunny.normal[fn.z-1].y,  Globals::bunny.normal[fn.z-1].z);
        glVertex3d(Globals::bunny.position[fv.z-1].x, Globals::bunny.position[fv.z-1].y, Globals::bunny.position[fv.z-1].z);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
    glPopMatrix();
}

void Window::displayDragonCallback(){
    cerr << "displayDragonCallback called " << endl;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    
    glDisable(GL_LIGHTING);
   /*
    glPushMatrix();
    Matrix4 tmp = Matrix4();
    tmp.identity();
    tmp.makeTranslate(Globals::light.position->x, Globals::light.position->y, Globals::light.position->z);
    tmp.transpose();
    glLoadMatrixd(tmp.getPointer());
    glutSolidSphere(0.5,20,20);// for point light
    glPopMatrix();
*/
    glClearColor(0, 0, 0, 0);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

    /*  draw sphere in first row, first column
     *  diffuse reflection only; no ambient or specular
     */
    glPushMatrix();
    //lighting model for dragon
    Material dragon = Material(GL_FRONT_AND_BACK);
    dragon.setAmbient(mat_ambient);
    dragon.setDiffuse(mat_diffuse);
    dragon.setSpecular(mat_specular);
    dragon.setShininess(low_shininess);//dragon low shininess

    glMatrixMode(GL_MODELVIEW);
    Matrix4 glmatrix;
    glmatrix = Globals::dragon.getMatrix();
    double aspectRatio = (double)width/height;
    
    //make a scaling matrix for bunny based on the window height and width
    Matrix4 scalingMatrix = Matrix4();
    scalingMatrix.identity();
    double x_ratio = (2*(tan(30 * PI/ 180.0) * 20) * aspectRatio)/(Globals::dragon.x_biggest -Globals::dragon.x_smallest);
    double y_ratio = 2*(tan(30 * PI/ 180.0) * 20)/(Globals::dragon.y_biggest - Globals::dragon.y_smallest);
    double z_ratio = 40/(Globals::dragon.z_biggest - Globals::dragon.z_smallest);
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
    translation.makeTranslate(-Globals::dragon.center_x, -Globals::dragon.center_y, -Globals::dragon.center_z);
    translation.print("translation matrix :");
    
    //translation.print("translation matrix: ");
    glmatrix = glmatrix * scalingMatrix;
    glmatrix = glmatrix * translation;
    
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers

    
    for (int i = 0;i < Globals::dragon.face_normal.size();i++)
    {
        glBegin(GL_TRIANGLES);
        Vector3 fv = Globals::dragon.face_vertice[i];
        Vector3 fn = Globals::dragon.face_normal[i];
        
        glNormal3d(Globals::dragon.normal[fn.x-1].x, Globals::dragon.normal[fn.x-1].y,  Globals::dragon.normal[fn.x-1].z);
        glVertex3d(Globals::dragon.position[fv.x-1].x, Globals::dragon.position[fv.x-1].y, Globals::dragon.position[fv.x-1].z);
        
        glNormal3d(Globals::dragon.normal[fn.y-1].x, Globals::dragon.normal[fn.y-1].y,  Globals::dragon.normal[fn.y-1].z);
        glVertex3d(Globals::dragon.position[fv.y-1].x, Globals::dragon.position[fv.y-1].y, Globals::dragon.position[fv.y-1].z);
        
        glNormal3d(Globals::dragon.normal[fn.z-1].x, Globals::dragon.normal[fn.z-1].y,  Globals::dragon.normal[fn.z-1].z);
        glVertex3d(Globals::dragon.position[fv.z-1].x, Globals::dragon.position[fv.z-1].y, Globals::dragon.position[fv.z-1].z);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
    glPopMatrix();
}

void Window::displayBearCallback(){
    cerr << "displayBearCallback called " << endl;
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    /*
    glPushMatrix();
    Matrix4 tmp = Matrix4();
    tmp.identity();
    tmp.makeTranslate(Globals::light.position->x, Globals::light.position->y, Globals::light.position->z);
    tmp.transpose();
    glLoadMatrixd(tmp.getPointer());
    glutSolidSphere(0.5,20,20);// for point light
    glPopMatrix();
    */
    
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*  draw sphere in first row, first column
     *  diffuse reflection only; no ambient or specular
     */
    glPushMatrix();
    //lighting model for dragon
    Material bear = Material(GL_FRONT_AND_BACK);
    //bear.setColorIndexes(color_index);
    bear.setAmbient(mat_ambient);
    bear.setDiffuse(mat_diffuse);
    bear.setSpecular(mat_specular);
    bear.setShininess(low_shininess);//makes bunny more shiny

    glMatrixMode(GL_MODELVIEW);
    Matrix4 glmatrix;
    glmatrix = Globals::bear.getMatrix();
    double aspectRatio = (double)width/height;
    
    //make a scaling matrix for bunny based on the window height and width
    Matrix4 scalingMatrix = Matrix4();
    scalingMatrix.identity();
    double x_ratio = (2*(tan(30 * PI/ 180.0) * 20) * aspectRatio)/(Globals::bear.x_biggest -Globals::bear.x_smallest);
    double y_ratio = 2*(tan(30 * PI/ 180.0) * 20)/(Globals::bear.y_biggest - Globals::bear.y_smallest);
    double z_ratio = 40/(Globals::bear.z_biggest - Globals::bear.z_smallest);
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
    scalingMatrix.makeScale(0.9*scaling, 0.9*scaling,0.9*scaling);
    
    Matrix4 translation = Matrix4();
    translation.identity();
    translation.makeTranslate(-Globals::bear.center_x, -Globals::bear.center_y, -Globals::bear.center_z);
    glmatrix = glmatrix * scalingMatrix;
    glmatrix = glmatrix * translation;

    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    
    for (int i = 0;i < Globals::bear.face_normal.size();i++)
    {
        glBegin(GL_TRIANGLES);
        Vector3 fv = Globals::bear.face_vertice[i];
        Vector3 fn = Globals::bear.face_normal[i];
        
        glNormal3d(Globals::bear.normal[fn.x-1].x, Globals::bear.normal[fn.x-1].y,  Globals::bear.normal[fn.x-1].z);
        glVertex3d(Globals::bear.position[fv.x-1].x, Globals::bear.position[fv.x-1].y, Globals::bear.position[fv.x-1].z);
        
      
        glNormal3d(Globals::bear.normal[fn.y-1].x, Globals::bear.normal[fn.y-1].y,  Globals::bear.normal[fn.y-1].z);
        glVertex3d(Globals::bear.position[fv.y-1].x, Globals::bear.position[fv.y-1].y, Globals::bear.position[fv.y-1].z);
        
        glNormal3d(Globals::bear.normal[fn.z-1].x, Globals::bear.normal[fn.z-1].y,  Globals::bear.normal[fn.z-1].z);
        glVertex3d(Globals::bear.position[fv.z-1].x, Globals::bear.position[fv.z-1].y, Globals::bear.position[fv.z-1].z);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
    glPopMatrix();
}


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

void Window::processSpecialKeys(int key, int x, int y){
    //display bunny
    if(key ==GLUT_KEY_F1){
        bunny = true;
        dragon = false;
        bear = false;
        //glutMouseFunc sets the mouse callback for the current window.
        glutMouseFunc(onMouseClick);
        glutMotionFunc(motionCallback);// register motion callback
        glutDisplayFunc(Window::displayBunnyCallback);
        glutIdleFunc(Window::idleBunnyCallback);
        glutKeyboardFunc(Window::processBunnyNormalKeys);
    }
    //display dragon
    if(key ==GLUT_KEY_F2){
      bunny = false;
      dragon = true;
      bear = false;
      //glutMouseFunc sets the mouse callback for the current window.
      glutMouseFunc(onMouseClick);
      glutMotionFunc(motionCallback);// register motion callback
      glutDisplayFunc(Window::displayDragonCallback);
      glutIdleFunc(Window::idleDragonCallback);
      glutKeyboardFunc(Window::processDragonNormalKeys);
    }
    //display dragon
    if(key ==GLUT_KEY_F3){
      bunny = false;
      dragon = false;
      bear = true;
      //glutMouseFunc sets the mouse callback for the current window.
      glutMouseFunc(onMouseClick);
      glutMotionFunc(motionCallback);// register motion callback
      glutDisplayFunc(Window::displayBearCallback);
      glutIdleFunc(Window::idleBearCallback);
      glutKeyboardFunc(Window::processBearNormalKeys);
    }
    else if(key == GLUT_KEY_LEFT){
        Globals::light.position->x = --Globals::light.position->x;
        cout << "light is moving " << endl;
    }
    else if(key == GLUT_KEY_RIGHT){
        Globals::light.position->x = ++Globals::light.position->x;
    }
    else if(key == GLUT_KEY_UP){
        Globals::light.position->y = ++Globals::light.position->y;
    }else if(key == GLUT_KEY_DOWN){
        Globals::light.position->y = --Globals::light.position->y;
    }
}

void Window::processBunnyNormalKeys(unsigned char key, int x, int y){
    if(key == 27)
        exit(0);
    else if(key == 's'){
        Globals::bunny.scale(0.9);
        displayBunnyCallback();
    }
    else if(key == 'S'){
        Globals::bunny.scale(1.1);
        displayBunnyCallback();
    }
    // move cube left by a small amount
    else if(key == 'x'){
        Globals::bunny.moveLeft();
        //displayBunnyCallback();
    }
    // move the cube right by a small amount
    else if (key == 'X'){
        Globals::bunny.moveRight();
        //displayBunnyCallback();
    }
    // move the cube down by a small amount
    else if (key == 'y'){
       Globals::bunny.moveDown();
       //displayBunnyCallback();
    }
    // move the cube up by a small amount
    else if (key == 'Y'){
        Globals::bunny.moveUp();
        //displayBunnyCallback();
    }
    // move the cube zzinto the screen by a small amount
    else if(key == 'z'){
        Globals::bunny.moveInto();
        displayBunnyCallback();
    }
    // move the cube out of the screen by a small amount
    else if(key == 'Z'){
        Globals::bunny.moveOutOf();
        displayBunnyCallback();
    }
    else if(key== 'r'){
        Globals::bunny.spin(1.0);
        displayBunnyCallback();
    }
    else if(key == '1'){
        --Globals::light.position->z;
    }else if(key == '2'){
        ++Globals::light.position->z;
    }
}

void Window::processDragonNormalKeys(unsigned char key, int x, int y){
    if(key == 27)
        exit(0);
    else if(key == 's'){
        Globals::dragon.scale(0.9);
        displayDragonCallback();
    }
    else if(key == 'S'){
        Globals::dragon.scale(1.1);
        displayDragonCallback();
    }
    // move cube left by a small amount
    else if(key == 'x'){
        Globals::dragon.moveLeft();
    }
    // move the cube right by a small amount
    else if (key == 'X'){
        Globals::dragon.moveRight();
    }
    // move the cube down by a small amount
    else if (key == 'y'){
        Globals::dragon.moveDown();
    }
    // move the cube up by a small amount
    else if (key == 'Y'){
        Globals::dragon.moveUp();
    }
    // move the cube zzinto the screen by a small amount
    else if(key == 'z'){
        Globals::dragon.moveInto();
        displayDragonCallback();
    }
    // move the cube out of the screen by a small amount
    else if(key == 'Z'){
        Globals::dragon.moveOutOf();
        displayDragonCallback();
    }
    else if(key== 'r'){
        Globals::dragon.spin(1.0);
        displayDragonCallback();
    }
}
void Window::processBearNormalKeys(unsigned char key, int x, int y){
    if(key == 27)
        exit(0);
    else if(key == 's'){
        Globals::bear.scale(0.9);
        displayBearCallback();
    }
    else if(key == 'S'){
        Globals::bear.scale(1.1);
        displayBearCallback();
    }
    // move cube left by a small amount
    else if(key == 'x'){
        Globals::bear.moveLeft();
    }
    // move the cube right by a small amount
    else if (key == 'X'){
        Globals::bear.moveRight();
    }
    // move the cube down by a small amount
    else if (key == 'y'){
        Globals::bear.moveDown();
    }
    // move the cube up by a small amount
    else if (key == 'Y'){
        Globals::bear.moveUp();
    }
    // move the cube zzinto the screen by a small amount
    else if(key == 'z'){
        Globals::bear.moveInto();
    }
    // move the cube out of the screen by a small amount
    else if(key == 'Z'){
        Globals::bear.moveOutOf();
    }
    else if(key== 'r'){
        Globals::bear.spin(1.0);
    }
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
      //Globals::robot.scaling(0.9);
      //displayCallback();
     Globals::bunny.scale(0.9);
     displayBunnyCallback();
    }
    else if(key == 'S'){
      /*
      Globals::robot.scaling(1.1);
      displayCallback();
      */
        Globals::bunny.scale(1.1);
        displayBunnyCallback();
    }
    //key for army
    else if(key == 'a'){
        displayArmy = !displayArmy;
        displayCallback();
      }
}

//for mouse control
void Window::onMouseClick(int button, int state, int x, int y) {
    //rotate the object around
    switch (button) {
        case GLUT_LEFT_BUTTON:
            cout << "enter left_button state " << endl;
            movement = 1; //set the correct state for motions
            // Map the mouse position to a logical sphere location.
            // Keep it in the class variable lastPoint.
            cout << "movement is " << movement << endl;
            lastPoint = trackBallMapping(x,y);
            glMatrixMode( GL_MODELVIEW );
            break;
        case GLUT_RIGHT_BUTTON:
            cout << "enter right_button state " << endl;
            movement = 2; //set the correct state for motions
            // Map the mouse position to a logical sphere location.
            // Keep it in the class variable lastPoint.
            cout << "movement is " << movement << endl;
            lastPoint = trackBallMapping(x,y);
            lastPoint_z = Vector3(x, y, 0);
            glMatrixMode( GL_MODELVIEW );
            break;
            
        default:
            break;
    }
}

// Treat the mouse position as the projection of a point on the hemi-sphere down to the image plane (along the z-axis), and determine that point on the hemi-sphere.
Vector3 Window::trackBallMapping( int x, int y ){
    Vector3 v = Vector3(1,1,1);
    float d;
    v.x = (2.0 * x - Window::width) / Window::width;
    v.y = (Window::height - 2.0 * y) / Window::height;
    v.z = 0.0; // pt lie on a 2D circle
    d = v.length();
    d = (d<1.0) ? d : 1.0;//default the radius of the circle is 1.0
    v.z = sqrtf(1.001 - d*d);
    v.normalize(); // Still need to normalize, since we only capped d, not v.
    return v;
}

void Window::motionCallback(int x, int y){
    cout << "in motionCallback " << endl;
    //
    // Handle any necessary mouse movements
    //
    Vector3 direction = Vector3(1,1,1);
    float pixel_diff;
    float rot_angle, zoom_factor;
    Vector3 curPoint = Vector3(1,1,1);
    switch (movement)
    {
            
        case 1 : // Left-mouse button is being held down
        {
            curPoint = trackBallMapping(x,y); // Map the mouse position to a logical
            // sphere location.
            direction = curPoint - lastPoint;
            float velocity = direction.length();
            if( velocity > 0.0001 ) // If little movement - do nothing.
            {
            //Determine the great circle connecting the old mouse-hemi-sphere point to the current mouse-hemi-sphere point.
            // Rotate about the axis that is perpendicular to the great circle connecting the mouse movements.
            Vector3 rotAxis = Vector3(1, 1, 1);
            //the normal will be the axis which rotate about
            rotAxis = lastPoint.cross(lastPoint,curPoint);
            rot_angle = velocity * 100;
            
            //Read off the current matrix, since we want this operation to be the last transformation, not the first, and OpenGL does things LIFO.
            //get the current matrix and save it
            Matrix4 rot = Matrix4();
            rot.identity();
            rot.makeRotate(rot_angle, rotAxis);
            //update the currect model2world
                if(bunny == true){
                    Globals::bunny.model2world = Globals::bunny.model2world * rot;
                    //force a redraw of scene
                    displayBunnyCallback();
                }else if(dragon == true){
                    Globals::dragon.model2world = Globals::dragon.model2world * rot;
                    //force a redraw of scene
                    displayDragonCallback();
                }else if(bear == true){
                    Globals::bear.model2world = Globals::bear.model2world * rot;
                    //force a redraw of scene
                    displayBearCallback();
                }
            }
            break;//break out of case 1
        }//end of case 1
        case 2: //Right-mouse button is being held down
        {
            // Zoom into or away from the scene based upon how far the
            // mouse moved in the x-direction.
            // This implementation does this by scaling the eye-space.
            //move left is negative (zoom out), move right is positive, zoom in
            pixel_diff = y - lastPoint_z.y;//signed distance about y coordinate
            zoom_factor = 1.0 + pixel_diff/40;
            /*
            if(pixel_diff > 0){
                zoom_factor = zoom_factor/10;
            }else{
                zoom_factor = 10/zoom_factor;
            }*/
            cout << "zoom factor is " << zoom_factor << endl;
            Matrix4 scale = Matrix4();
            scale.identity();
            scale.makeScale(zoom_factor, zoom_factor, zoom_factor);
           
            //glScalef( zoom_factor, zoom_factor, zoom_factor );
            // Set the current point, so the lastPoint will be saved properly below .
            //
            curPoint.x = (float)x;
            curPoint.y = (float)y;
            curPoint.z = 0;
            
            //update the currect model2world
            if(bunny == true){
               Globals::bunny.model2world = Globals::bunny.model2world * scale;
                //force a redraw of scene
                displayBunnyCallback();
            }else if(dragon == true){
                Globals::dragon.model2world = Globals::dragon.model2world * scale;
                //force a redraw of scene
                displayDragonCallback();
            }else if(bear == true){
                Globals::bear.model2world = Globals::bear.model2world * scale;
                //force a redraw of scene
                displayBearCallback();
            }
            // If we want to see it, we need to force the system to redraw the scene.
            break;
        }//end of case 2
        
    }//end of switch
    // Save the location of the current point for the next movement.
    //
    lastPoint = curPoint;
}//end of function
