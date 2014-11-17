//
//  MatrixTransform.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__MatrixTransform__
#define __CSE167HW1__MatrixTransform__

#include <stdio.h>
#include "Group.h"
#include "Matrix4.h"
#include "Cube_Geode.h"
#include "Sphere.h"

class MatrixTransform : public Group{
    public:
        MatrixTransform();
        MatrixTransform(Matrix4);
        Matrix4 getMatrixTransform();
        void draw(Matrix4 C);
        void drawBoundingBox(Matrix4);
        Matrix4 M;//transform matrix M
};

#endif /* defined(__CSE167HW1__MatrixTransform__) */
