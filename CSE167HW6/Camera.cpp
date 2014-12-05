//
//  Camera.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/21/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Camera.h"
#include <GLUT/glut.h>

//constructor of Camera object
Camera::Camera(){
    c.identity();
    center_e = new Vector3(0,15,15);
    up = new Vector3(0,1,0);
    look_at_d = new Vector3(0,0,0);
}

void Camera::set(Vector3& e,Vector3& d, Vector3& up){
    //calculate z-axis
     Vector3 z_axis = e-d;
     z_axis.normalize();
     
     //calculate x_axis
     Vector3 x_axis = up.cross(up, z_axis);
     x_axis.normalize();
     
     //calculate y-axis
     Vector3 y_axis = z_axis.cross(z_axis, x_axis);
    
    //row-major ordering of the camera matrix
    c = Matrix4(x_axis,y_axis,z_axis,e,0.0,0.0,0.0,1.0);
    this->inverse();
}

//getCameraMatrix will call the inverse camera matrix
Matrix4& Camera::getCameraMatrix(){
    //inverse();
    return c;
}

void Camera::set(){
    this->set(*(this->center_e), *(this->look_at_d), *(this->up));
}

//inverse of the camera matrix
void Camera::inverse(){
    //use the formula to do inverse of R times the inverse of T
    //rotation matrix
    Matrix4 rotate = c;
    rotate.m[0][3] = 0;
    rotate.m[1][3] = 0;
    rotate.m[2][3] = 0;
    rotate.m[3][3] = 1;
    rotate.m[3][0] = 0;
    rotate.m[3][1] = 0;
    rotate.m[3][2] = 0;
   
    // inverse of R = transpose of R
    rotate.transpose();
    
    Matrix4 translate = Matrix4();
    translate.makeTranslate(-c.m[0][3], -c.m[1][3], -c.m[2][3]);
    c  = rotate * translate;
}

//change the eye position and update the camera matrix before inverse
void Camera::xDown(){
    --(this->center_e->x);
    this->set(*(this->center_e), *(this->look_at_d), *(this->up));
}

void Camera::xUp(){
    ++(this->center_e->x);
    this->set(*(this->center_e), *(this->look_at_d), *(this->up));
}

void Camera::yDown(){
    --(this->center_e->y);
    this->set(*(this->center_e), *(this->look_at_d), *(this->up));
}

void Camera::yUp(){
    ++(this->center_e->y);
    this->set(*(this->center_e), *(this->look_at_d), *(this->up));
}

void Camera::zDown(){
    --(this->center_e->z);
    this->set(*(this->center_e), *(this->look_at_d), *(this->up));
}

void Camera::zUp(){
    ++(this->center_e->z);
    this->set(*(this->center_e), *(this->look_at_d), *(this->up));
}