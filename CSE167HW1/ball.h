//
//  ball.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/14/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__ball__
#define __CSE167HW1__ball__

#include <stdio.h>
#include "Matrix4.h"
#include "Vector4.h"

class ball{
    protected:
        Matrix4 model2world;  // model matrix (transforms model coordinates to world coordinates)
        Vector4 *position;
    
    public:
        ball(); //constructor
        Matrix4& getMatrix(); //return the model2world matrix
        void fall(double);
        float getY();
        float getX();
        float getZ();
        void moveX(double);
};






#endif /* defined(__CSE167HW1__ball__) */
