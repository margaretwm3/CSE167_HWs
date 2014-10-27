//
//  Vector4.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Vector4.h"
#include <iostream>

using namespace std;

//constructor with four parameters for the vector coordinates
Vector4::Vector4(double x, double y, double z, double w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

// overload operator '+' for addition
Vector4 Vector4::operator+(const Vector4& vec){
    double result_x = this->x + vec.x;
    double result_y = this->y + vec.y;
    double result_z = this->z + vec.z;
    double result_w = this->w + vec.w;
    Vector4 *result = new Vector4(result_x,result_y,result_z,result_w);
    return *result;
}

//overload operator '-' for subtraction
Vector4 Vector4::operator-(const Vector4& vec){
    double result_x = this->x - vec.x;
    double result_y = this->y - vec.y;
    double result_z = this->z - vec.z;
    double result_w = this->w - vec.w;
    Vector4 *result = new Vector4(result_x,result_y,result_z,result_w);
    return *result;
}

//dehomogenize the vector (scale it so that its fourth component is equal to one)
void Vector4::dehomogenize(){
    /* 
       when divide 0, it might cause an exception
     */
    this-> x = this->x / this->w;
    this-> y = this->y / this->w;
    this-> z = this->z / this->w;
    this-> w = this->w / this->w;
}

//print x,y, z and w components of the vector after a comment string
void Vector4::print(string comment){
    cout << comment << this-> x << " " << this-> y << " "<< this-> z << " " << this-> w << endl;
}

