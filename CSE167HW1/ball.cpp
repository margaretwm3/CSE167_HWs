//
//  ball.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/14/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "ball.h"

ball::ball(){
    position = new Vector4(0,0,0,1);
    model2world.identity();
}

Matrix4& ball::getMatrix()
{
    return model2world;
}

void ball::fall(double distance){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0, -distance,0);
    model2world = tmp * model2world;
    
    *position = tmp* * position; //calculate the ball position
    position->dehomogenize(); //how much it moves based on the position vector
}

void ball::moveX(double distance){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(-distance, 0, 0);
    model2world = tmp * model2world;
    *position = tmp * *position;
    position -> dehomogenize();
}

float ball::getY(){
    position -> dehomogenize();
    return position->y;
}

float ball::getX(){
    position -> dehomogenize();
    return position->x;
}

float ball::getZ(){
    position->dehomogenize();
    return position->z;
}
