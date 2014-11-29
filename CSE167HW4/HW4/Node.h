//
//  Node.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Node__
#define __CSE167HW1__Node__

#include <stdio.h>
#include "Matrix4.h"
#include "Vector4.h"
#include <string>
#include <iostream>

/*
 * This class is an abstract class and serve as a base class
 */
class Node{

public:
    string name;
    float radius;//keep track of the radius of the bounding box
    Node();
    Node(string);
    string getName();
    void setName(string);
    Node* getParent();
    void setParent(Node*); // set the parent appropriately
    //for the bounding box
    Vector4 center = Vector4(0,0,0,1);
    Vector4 scale = Vector4(0.5,0.5,0.5,0);
    //pure virtual function makes this class an abstract class
    virtual void draw(Matrix4 C) = 0;
    virtual void update() = 0;
    virtual void drawBoundingBox(Matrix4 C) = 0;
private:
   
    Node* parent;
};

#endif /* defined(__CSE167HW1__Node__) */
