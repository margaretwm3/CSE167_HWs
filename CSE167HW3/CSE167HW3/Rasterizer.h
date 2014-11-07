//
//  Rasterizer.h
//  CSE167HW3
//
//  Created by Mingshan Wang on 11/4/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#ifndef __CSE167HW3__Rasterizer__
#define __CSE167HW3__Rasterizer__
#define M_PI 3.14159265358979323846

#include <stdio.h>
#include "Vector4.h"

    void loadData();
    void clearBuffer();// Clear frame buffer
    void drawPoint(int x, int y, float r, float g, float b, int pointSize);  // Draw a point into the frame buffer
    void rasterize();
    void reshapeCallback(int new_width, int new_height);// Called whenever the window size changes
    void keyboardCallback(unsigned char key, int, int);
    void processSpecialKeys(int key, int x, int y);
    //void spin(double deg); // deg in degress
    void displayCallback();
    void idleCallback();


#endif /* defined(__CSE167HW3__Rasterizer__) */
