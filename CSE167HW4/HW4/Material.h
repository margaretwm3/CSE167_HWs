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
    int lightNumber;
    GLenum front_and_back;
    
    Material();
    Material(GLenum);
    
    void setAmbient(GLfloat*);
    void setDiffuse(GLfloat*);
    void setAmbientAndDiffuse(GLfloat*);
    void setSpecular(GLfloat*);
    void setShininess(GLfloat*);
    void setColorIndexes(GLfloat *v);
};

#endif /* defined(__HW4__Material__) */
