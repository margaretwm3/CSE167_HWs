//
//  Material.h
//  HW4
//
//  Created by Mingshan Wang on 11/18/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __HW4__Material__
#define __HW4__Material__

#include <stdio.h>
#include <GLUT/glut.h>

class Material
{
public:
   
    GLfloat mat_ambient[4] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_diffuse[4] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[1] = { 129 };
    GLfloat mat_ambient_color[4] = { 0.f, .8f, .8f, 1.f};
    
    Material();

    
    void setAmbient(float,float,float,float);
    void setDiffuse(float,float,float,float);
    void setSpecular(float,float,float,float);
    void setShininess(float);

};

#endif /* defined(__HW4__Material__) */
