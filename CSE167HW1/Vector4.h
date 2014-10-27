//
//  Vector4.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Vector4__
#define __CSE167HW1__Vector4__

#include <stdio.h>
#include <string>
using namespace std;

class Vector4{
  protected:
    double x,y,z,w;

  public:
    //constructor with four parameters for the vector coordinates
    Vector4(double x, double y, double z, double w);
    // overload operator '+' for addition
    Vector4 operator+(const Vector4&);
    //overload operator '-' for subtraction
    Vector4 operator-(const Vector4&);
    //dehomogenize the vector (scale it so that its fourth component is equal to one)
    void dehomogenize();
    //print x,y, z and w components of the vector after a comment string
    void print(string comment);
    friend class Matrix4;
    friend class Window;
    friend class ball;

};

#endif /* defined(__CSE167HW1__Vector4__) */
