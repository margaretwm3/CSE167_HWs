//
//  bunny.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/22/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__bunny__
#define __CSE167HW1__bunny__

#include <stdio.h>
#include "Matrix4.h"
#include "Vector3.h"
#include "Window.h"
#include <iostream>
#include <vector>

class bunny{

public:
    bunny(); //constructor
    Matrix4 model2world;  // model matrix (transforms model coordinates to world coordinates)
    Matrix4& getMatrix(); //return the model2world matrix
    void spin(double);      // spin cube [degrees]
    void scale(double scale);
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    void moveInto();
    void moveOutOf();
    vector<Vector3> position;
    vector<Vector3>normal;
    vector<Vector3>color;
    vector<Vector3> face_vertice;//vector of face vertices
    vector<Vector3> face_normal; //vector of face normal
    double x_smallest = 100;
    double x_biggest = 0;
    double y_smallest = 100;
    double y_biggest = 0;
    double z_smallest = 100;
    double z_biggest = 0;
    //calculate the center of the model
    double center_x, center_y,center_z;
};

#endif /* defined(__CSE167HW1__bunny__) */
