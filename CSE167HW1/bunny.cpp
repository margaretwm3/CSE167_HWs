//
//  bunny.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/22/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "bunny.h"

bunny::bunny(){
    model2world.identity();
}

Matrix4& bunny::getMatrix()
{
    return model2world;
}

// rotate along y axis
void bunny::spin(double angle){
    Matrix4 tmp = Matrix4();
    tmp.makeRotateY(angle);
    model2world = model2world*tmp;
}