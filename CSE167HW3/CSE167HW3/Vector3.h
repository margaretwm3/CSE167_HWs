//
//  Vector3.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/8/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Vector3__
#define __CSE167HW1__Vector3__

#include <stdio.h>
#include <string>
using namespace std;

class Vector3{
    protected:
        double x,y,z;   // vector elements;
    
    public:
        //constructor with three parameters for three vecotr coordinates
        Vector3(double x, double y, double z);
    
        //overload operator '+' for addition
        Vector3 operator+(const Vector3&);
    
        //overload operator '-' for subtraction
        Vector3 operator-(const Vector3&);
    
        //negation
        void negate();
    
        //scale (multiplication with scalar value)
        void scale(double s);
    
        //dot product, returns result
        double dot(const Vector3&, const Vector3&);
    
        //cross product, returns result and puts it in calling vector
        Vector3 cross(const Vector3&, const Vector3&);
    
        //length ot the vector
        double length();
    
        //normalize the vector (make it so that its length is equal to one)
        void normalize();
    
        double getX();
        double getY();
        double getZ();
    
        // print x,y and z components of the vector after a comment string
        void print(string comment);
        friend class Matrix4;
        friend class Camera;
        friend class Window;
};



#endif /* defined(__CSE167HW1__Vector3__) */
