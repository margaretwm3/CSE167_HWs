//
//  Group.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Group__
#define __CSE167HW1__Group__

#include <stdio.h>
#include "Node.h"
#include <list>

using namespace std;

class Group: public Node{
public:
    Group();
    int numOfChild = 0;
    void addChild(Node*);//add child nodes
    void removeChild(string);//remove child nodes
    //draw method needs to traverse the list of children and call each child node's draw function.
    void draw(Matrix4 C);
    void update();
    void drawBoundingBox(Matrix4 C);
    friend class MatrixTransform;
    friend class Window;
    
private:
    //store a list of pointers to child nodes
    list<Node*> nodeList;
    
};


#endif /* defined(__CSE167HW1__Group__) */
