//
//  dragon.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/22/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "dragon.h"

dragon::dragon(){
    model2world.identity();
}

Matrix4& dragon::getMatrix()
{
    return model2world;
}

// rotate along y axis
void dragon::spin(double angle){
    Matrix4 tmp = Matrix4();
    tmp.makeRotateY(angle);
    model2world = model2world*tmp;
}
void dragon::scale(double scale){
    Matrix4 tmp = Matrix4();
    //tmp.identity();
    tmp.makeScale(scale, scale, scale);
    // the order is important to keep in the local space
    model2world = model2world * tmp;
    
}