//
//  Rasterizer.h
//  CSE167HW3
//
//  Created by Mingshan Wang on 11/4/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW3__Rasterizer__
#define __CSE167HW3__Rasterizer__

#include <stdio.h>
#include "Vector4.h"

    void loadData();
    void clearBuffer();// Clear frame buffer
    void drawPoint(int x, int y, float r, float g, float b);  // Draw a point into the frame buffer
    void rasterize();
    void reshapeCallback(int new_width, int new_height);// Called whenever the window size changes
    void keyboardCallback(unsigned char key, int, int);
    void displayCallback();
    

#endif /* defined(__CSE167HW3__Rasterizer__) */
