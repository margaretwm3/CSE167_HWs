//
//  Geode.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Geode__
#define __CSE167HW1__Geode__

#include <stdio.h>
#include "Node.h"

//abstract class Geode, it should set OpenGL's ModelView matrix to the current C matrix
class Geode : public Node{
public:
    Geode();
    void setModelView(Matrix4);
    void draw(Matrix4 C);
    void update();
    //abstract render function to render its geometry
    virtual void render() = 0;
};

#endif /* defined(__CSE167HW1__Geode__) */
