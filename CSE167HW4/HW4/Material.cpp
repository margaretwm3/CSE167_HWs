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
    front_and_back = GL_FRONT_AND_BACK;
}

Material::Material(GLenum fb) {
    front_and_back = fb;
}

void Material::setAmbient(GLfloat *v) {
    //The glMaterialfv function specifies material parameters for the lighting model.
    glMaterialfv(front_and_back , GL_AMBIENT, v);
}

void Material::setDiffuse(GLfloat *v) {
    glMaterialfv(front_and_back , GL_DIFFUSE, v);
}

void Material::setAmbientAndDiffuse(GLfloat *v) {
    glMaterialfv(front_and_back , GL_AMBIENT_AND_DIFFUSE, v);
}

void Material::setSpecular(GLfloat *v) {
    glMaterialfv(front_and_back , GL_SPECULAR, v);
}

void Material::setShininess(GLfloat *v) {
    glMaterialfv(front_and_back , GL_SHININESS, v);
}


void Material::setColorIndexes(GLfloat *v) {
    glMaterialfv(front_and_back, GL_COLOR_INDEXES, v);
}

