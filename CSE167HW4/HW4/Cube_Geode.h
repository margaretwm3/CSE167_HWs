//
//  Cube_Geode.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Cube_Geode__
#define __CSE167HW1__Cube_Geode__

#include <stdio.h>
#include "Geode.h"
#include "Vector4.h"

//derived from Geode
class Cube_Geode: public Geode{

public:
    Cube_Geode();
    //void draw(Matrix4 C);
    void render();
    void drawBoundingBox(Matrix4 C);
};

#endif /* defined(__CSE167HW1__Cube_Geode__) */
