//
//  Vector3.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/8/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Vector3.h"
#include <cmath>
#include <iostream>
using namespace std;

//constructor with three parameters for three vecotr coordinates
Vector3::Vector3(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

//overload operator '+' for addition
Vector3 Vector3::operator+(const Vector3& vec2){
    double x3 = this->x + vec2.x;
    double y3 = this->y + vec2.y;
    double z3 = this->z + vec2.z;
    Vector3 *result = new Vector3(x3,y3,z3);
    
    return *result;
}

//overload operator '-' for subtraction
Vector3 Vector3::operator-(const Vector3& vec2){
    double x3 = this->x - vec2.x;
    double y3 = this->y - vec2.y;
    double z3 = this->z - vec2.z;
    Vector3 *result = new Vector3(x3,y3,z3);
    
    return *result;
}

//negation
void Vector3::negate(){
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

//scale (multiplication with scalar value)
void Vector3::scale(double s){
    this->x *= s;
    this->y *= s;
    this->z *= s;
}

//dot product, returns result
double Vector3::dot(const Vector3& v1, const Vector3& v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//cross product, returns result and puts it in calling vector
Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2){
    double x3 = v1.y * v2.z - v1.z * v2.y;
    double y3 = v1.z * v2.x - v1.x * v2.z;
    double z3 = v1.x * v2.y - v1.y * v2.x;
    Vector3 *result = new Vector3(x3,y3,z3);
    return *result;
}

//length ot the vector
double Vector3::length(){
    double result = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return result;
}

//normalize the vector (make it so that its length is equal to one)
void Vector3::normalize(){
    double len = this->length();

    this-> x = this->x/ len;
    this-> y = this->y/ len;
    this-> z = this->z/ len;
}

double Vector3::getX(){
    return this->x;
}

double Vector3::getY(){
    return this->y;
}

double Vector3::getZ(){
    return this->z;
}

void Vector3::incX(){
    this->x++;
}

void Vector3::incY(){
    this->y++;
}

void Vector3::incZ(){
    this->z++;
}

void Vector3::decX(){
    this->x--;
}

void Vector3::decY(){
    this->y--;
}

void Vector3::decZ(){
    this->z--;
}


// print x,y and z components of the vector after a comment string
void Vector3::print(string comment){
    cout << comment << this-> x << " " << this->y << " " << this->z << " " << endl;

}