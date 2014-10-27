//
//  dragon.h
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/22/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW1__dragon__
#define __CSE167HW1__dragon__

#include <stdio.h>
#include "Matrix4.h"

class dragon{
protected:
    Matrix4 model2world;  // model matrix (transforms model coordinates to world coordinates)
    
public:
    dragon(); //constructor
    Matrix4& getMatrix(); //return the model2world matrix
    void spin(double);      // spin cube [degrees]

};


#endif /* defined(__CSE167HW1__dragon__) */
