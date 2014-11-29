//
//  Geode.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Geode.h"
#include <GLUT/GLUT.h>

Geode::Geode(){}

void Geode::setModelView(Matrix4 current){
    glMatrixMode(GL_MODELVIEW);
    current.transpose();
    glLoadMatrixd(current.getPointer());
    current.transpose();
}

void Geode::update(){

}

void Geode::draw(Matrix4 current){
    glMatrixMode(GL_MODELVIEW);
    current.transpose();
    glLoadMatrixd(current.getPointer());
    current.transpose();
    render();//call geometry's own render function
}
