//
//  MatrixTransform.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "MatrixTransform.h"
#include "main.h"

MatrixTransform::MatrixTransform(){
    this->M = Matrix4();
    M.identity();
}

MatrixTransform::MatrixTransform(Matrix4 m){
    this->M = m;
}

Matrix4 MatrixTransform::getMatrixTransform(){
    return this->M;
}

//times the M matrix stores on the right
void MatrixTransform::draw(Matrix4 C){
    Matrix4 tmp = C * M;
    list<Node*>::iterator iter = nodeList.begin();
    list<Node*>::iterator end = nodeList.end();
    for(;iter!=end;++iter){
        (*iter)->draw(tmp);
    }
}

void MatrixTransform::drawBoundingBox(Matrix4 C){
    double xmin = 1000;
    double xmax = -1000;
    double ymin = 1000;
    double ymax = -1000;
    double zmin = 1000;
    double zmax = -1000;
    Matrix4 tmp = C * M;
    list<Node*>::iterator iter = nodeList.begin();
    list<Node*>::iterator end = nodeList.end();
    for(;iter!=end;++iter){
        //call geometry's own draw bounding box
        (*iter)->drawBoundingBox(tmp);
    }
    if(Globals::boundingBox){
        iter = nodeList.begin();
        end = nodeList.end();
    
        //Need to draw the bounding box for the whole robot
        for(;iter!=end;++iter){
            if((*iter)->center.x + (*iter)->radius > xmax){
                xmax =(*iter)->center.x + (*iter)->radius;
            }
            if((*iter)->center.x - (*iter)->radius < xmin){
                xmin =(*iter)->center.x - (*iter)->radius;
            }
            if((*iter)->center.y + (*iter)->radius > ymax){
                ymax =(*iter)->center.y + (*iter)->radius;
            }
            if((*iter)->center.y - (*iter)->radius < ymin){
                ymin =(*iter)->center.y - (*iter)->radius;
            }
            if((*iter)->center.z + (*iter)->radius > zmax){
                zmax =(*iter)->center.z + (*iter)->radius;
            }
            if((*iter)->center.z - (*iter)->radius < zmin){
                zmin =(*iter)->center.z - (*iter)->radius;
            }
         }
    cout << xmin << " " << xmax << endl;
    cout << ymin << " " << ymax << endl;
    cout << zmin << " " <<zmax << endl;
    
    if(xmax - xmin > ymax-ymin){
        radius = xmax-xmin;
    }else{
        radius = ymax-ymin;
    }
    
    if(zmax-zmin > radius){
        radius = zmax - zmin;
    }
    cout << xmax-xmin << endl;
    cout << ymax-ymin << endl;
    cout << zmax-zmin << endl;
    
    cout << radius << endl;
    
    center = Vector4(0,0,0,1);
    center  = tmp * center;
    Matrix4 translate = Matrix4();
    translate.identity();
    translate.makeTranslate(center.x, center.y, center.z);
    Matrix4 scalingMatrix = Matrix4();
    scalingMatrix.identity();
    scalingMatrix.makeScale(radius/2, radius/2, radius/2);
    Matrix4 result = translate * scalingMatrix;
    
    glPushMatrix();
    glColor3f(0, 0, 1);
    result.transpose();
    glLoadMatrixd(result.getPointer());
    glutWireSphere(1.3, 20, 20);
    glPopMatrix();
  }
}