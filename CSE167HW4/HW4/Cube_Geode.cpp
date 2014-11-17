//
//  Cube_Geode.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Cube_Geode.h"
#include "main.h"
#include <GLUT/glut.h>

Cube_Geode::Cube_Geode(){
    center = Vector4(0,0,0,1);
    scale = Vector4(0.5,0.5,0.5,0);
    radius = 1.5;
}

/*
void Cube_Geode::draw(Matrix4 C){
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    
    glColor3f(0.5,0.0,1.0);
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    // Tell OpenGL what ModelView matrix to use:
    C.transpose();
    glLoadMatrixd(C.getPointer());
    glutSolidCube(3);
    //if the flag drawBoundingbox is true
    if(Globals::boundingBox){
        cout << this->getName() << " drawing bounding box " << endl;
        drawBoundingBox(C);
    }
}
 */

void Cube_Geode::render(){
    glColor3f(0.5,0.0,1.0);
    glutSolidCube(3);
}

//the method used to draw bounding box
void Cube_Geode::drawBoundingBox(Matrix4 C){
    if(Globals::boundingBox){
        cout << this->getName() << " drawing bounding box " << endl;
     Vector4 newCenter = Vector4(0,0,0,1);//it is a point
     Vector4 newScale = Vector4(0.5,0.5,0.5,0);//it is a vector
    
     newCenter = C * center;
     newScale = C * scale;
     center = newCenter;
     scale = newScale;
     float len = newScale.length();
      radius = len;//update the radius
     //cout << "length is " << len << endl;

     Matrix4 trans = Matrix4();
     trans.identity();
     trans.makeTranslate(newCenter.x, newCenter.y, newCenter.z);
     Matrix4 scalingMatrix = Matrix4();
     scalingMatrix.identity();
     scalingMatrix.makeScale(len, len, len);
     Matrix4 result = trans * scalingMatrix;
    
    glPushMatrix();
    //read for cube bounding box
    glColor3f(1,0.0,0.0);
    result.transpose();
    glLoadMatrixd(result.getPointer());
    glutWireSphere(3,20,20);
    glPopMatrix();
 }
}


