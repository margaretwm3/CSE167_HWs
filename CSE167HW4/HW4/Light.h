//
//  Light.h
//  HW4
//
//  Created by Mingshan Wang on 11/18/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __HW4__Light__
#define __HW4__Light__

#include <stdio.h>
#include "Vector4.h"
#include "Vector3.h"
#include <GLUT/GLUT.h>

class Light{
public:
    Light();
    //create three seperate light positions
    GLfloat light_position[4] = { 1.0,3.0,7.0, 1.0 };
    GLfloat light_position_s[4] = {3.0, 3.0, 9.0, 1.0};
    GLfloat light_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
    
    void setLightPosition(float,float,float,float);
};

#endif /* defined(__HW4__Light__) */
