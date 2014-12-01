//
//  Light.cpp
//  HW4
//
//  Created by Mingshan Wang on 11/18/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Light.h"

Light::Light(){
}

void Light::setLightPosition(float x, float y, float z,float w){
    this->light_position[0] = x;
    this->light_position[1] = y;
    this->light_position[2] = z;
    this->light_position[3] = w;
}

