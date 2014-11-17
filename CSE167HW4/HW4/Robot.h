//
//  Robot.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/12/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Robot__
#define __CSE167HW1__Robot__

#include <stdio.h>
#include "Node.h"
#include "MatrixTransform.h"
#include "Sphere.h"
#include "Matrix4.h"
#include "Cube_Geode.h"
#include "Window.h"
// this class is used to draw a robot

class Robot{
public:
    Robot();
    MatrixTransform *root;//the root for everything
    MatrixTransform* buildRobot(double,double);
    void scaling(double);
    void setLocation(float,float,float);
};

#endif /* defined(__CSE167HW1__Robot__) */
