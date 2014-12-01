//
//  Material.cpp
//  HW4
//
//  Created by Mingshan Wang on 11/18/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Material.h"
#include <GLUT/glut.h>

using namespace std;


Material::Material() {
}

void Material::setAmbient(float x,float y,float z,float w){
    mat_ambient[0] = x;
    mat_ambient[1] = y;
    mat_ambient[2] = z;
    mat_ambient[3] = w;
}

void Material::setDiffuse(float x,float y,float z,float w){
    mat_diffuse[0] = x;
    mat_diffuse[1] = y;
    mat_diffuse[2] = z;
    mat_diffuse[3] = w;
}

void Material::setSpecular(float x,float y,float z,float w){
    mat_specular[0] = x;
    mat_specular[1] = y;
    mat_specular[2] = z;
    mat_specular[3] = w;
}

void Material::setShininess(float x){
    mat_shininess[0] = x;
}