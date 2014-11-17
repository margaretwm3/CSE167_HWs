//
//  Sphere.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Sphere__
#define __CSE167HW1__Sphere__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "Geode.h"

class Sphere: public Geode{
    public:
        Sphere();
        //void draw(Matrix4 C);
        void render();
        void update();
        void drawBoundingBox(Matrix4 C);

};

#endif /* defined(__CSE167HW1__Sphere__) */
