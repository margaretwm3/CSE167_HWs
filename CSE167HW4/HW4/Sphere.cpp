//
//  Sphere.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Sphere.h"
#include "main.h"
#include <GLUT/glut.h>

Sphere::Sphere(){
    center = Vector4(0,0,0,1);
    scale = Vector4(0.5,0.5,0.5,0);
    radius = 2;
}

void Sphere::render(){
    glColor3f(0.5,0.0,1.0);
    /*
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    // Tell OpenGL what ModelView matrix to use:
    C.transpose();
    glLoadMatrixd(C.getPointer());
     */
    glutSolidSphere(2.5,20,20);
}

void Sphere::drawBoundingBox(Matrix4 C){
    //if the flag drawBoundingbox is true
    if(Globals::boundingBox){
        cout << this->getName() << " drawing bounding box " << endl;
        C.print("C passed in boundingbox ");
        Vector4 newCenter = Vector4(0,0,0,1);
        Vector4 newScale = Vector4(0.5,0.5,0.5,0);
    
        newCenter = C * center;
        newScale = C * scale;
        float len = newScale.length();
        radius = len;
         
        Matrix4 *trans = new Matrix4();
        trans->identity();
        trans->makeTranslate(newCenter.x, newCenter.y, newCenter.z);
        trans->print("translation matrix : ");
        Matrix4 *scalingMatrix = new Matrix4();
        scalingMatrix->identity();
        scalingMatrix->makeScale(len, len, len);
        scalingMatrix->print("scaling matrix is ");
        Matrix4 result = (*trans) * (*scalingMatrix);
    
        glPushMatrix();
        //green for sphere bounding box
        glColor3f(0.0,1.0,0.0);
        result.transpose();
        glLoadMatrixd(result.getPointer());
        glutWireSphere(3,20,20);
        glPopMatrix();
    }
}

void Sphere::update(){}