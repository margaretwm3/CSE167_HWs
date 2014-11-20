//
//  Light.cpp
//  HW4
//
//  Created by Mingshan Wang on 11/18/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Light.h"

Light::Light(){
    position = new Vector4(1.0,1.0,5.0,1.0);//it is a pt
    color = new Vector3(1,0,0);
    direction = new Vector4(1, 1, 1,0.0);//it is a vector
    openAngle = 10;
    spot_width = 5;
    fAmbient = 1;
    fConstantAtt = 0.3;
    fLinearAtt = 0.007;
    fExpAtt = 0.00008;
}

//create spot light
void Light::setLightPosition(float a,float b,float c){
    position->x = a;
    position->y = b;
    position->z = c;
}



Vector4 Light::getPointLightColor(Light ptLight, Vector4 vWorldPos, Vector3 vNormal){
    //calcualte the distance
    Vector4 vPostoLight = vWorldPos - *(ptLight.position);
    float distance = vPostoLight.length();
    Vector3 tmp = Vector3(vPostoLight.x, vPostoLight.y, vPostoLight.z);
    tmp.normalize();
    tmp.x = -tmp.x;
    tmp.y = -tmp.y;
    tmp.z = -tmp.z;
    
    float dotResult = vNormal.dot(vNormal,tmp);
    //choose the max between zero and dotResult
    float fDiffuse;
    if(dotResult < 0){
        fDiffuse = 0;
    }
    else{
        fDiffuse = dotResult;
    }
    float fAttTotal = ptLight.fConstantAtt + ptLight.fLinearAtt*distance + ptLight.fExpAtt*distance * distance;
    float t = (ptLight.fAmbient+ fDiffuse)/fAttTotal;
    return Vector4((ptLight.color->x) * t, (ptLight.color->y) * t,
                   (ptLight.color->z) * t, 1 * t);
}
