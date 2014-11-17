//
//  Camera.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/21/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__Camera__
#define __CSE167HW1__Camera__

#include <stdio.h>
#include "Vector3.h"
#include "Matrix4.h"
#include <GLUT/glut.h>


class Camera{
    //member variables
    protected:
        Vector3 *center_e;
        Vector3 *up;
        Vector3 *look_at_d;
        Matrix4 c;
    
    public:
        Camera();
        //access the components of the camera matrix
        Matrix4& getCameraMatrix();
        GLdouble* getGLMatrix();
        void set(Vector3& e, Vector3& d, Vector3& up); // calculate the camera matrix
        void inverse();//calculate the inverse of the camera matrix
};



#endif /* defined(__CSE167HW1__Camera__) */


