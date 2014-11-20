//
//  Light.h
//  HW4
//
//  Created by Mingshan Wang on 11/18/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __HW4__Light__
#define __HW4__Light__

#include <stdio.h>
#include "Vector4.h"
#include "Vector3.h"

class Light{
public:
    Vector4 *position;
    Vector3 *color;
    Vector4 *direction;
    float openAngle;
    float fAmbient;
    
    //for spot light
    float spot_width; // small enough so that only illuminates part of the objects
    float fConstantAtt;
    float fLinearAtt;
    float fExpAtt;
    
    Light();
    Vector4 getPointLightColor(Light ptLight, Vector4 vWorldPos, Vector3 vNormal);
    void setLightPosition(float a, float b, float c);
    
};

#endif /* defined(__HW4__Light__) */
