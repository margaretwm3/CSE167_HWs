//
//  dragon.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/22/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__dragon__
#define __CSE167HW1__dragon__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Matrix4.h"
#include "Light.h"
#include "Material.h"
#include <vector>

class dragon{
public:
    dragon(); //constructor
    Matrix4& getMatrix(); //return the model2world matrix
    Matrix4 model2world;  // model matrix (transforms model coordinates to world coordinates)
    void spin(double);      // spin cube [degrees]
    void scale(double scale);
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    void moveInto();
    void moveOutOf();
    vector<Vector3>position;
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
   
    Light light;
    Matrix4 m2w_light;
    Matrix4 m2w_spotLight;
    void update();
    Material mat;
    double spot_light_angle;
};



#endif /* defined(__CSE167HW1__dragon__) */
