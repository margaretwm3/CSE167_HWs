#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Camera.h"
#include "Matrix4.h"

class Window	  // OpenGL output window related routines
{
    public:
        static int width, height; 	            // window size
        static int spin_direction;              // for change the spin direction
    
        static void idleCallback(void);
        static void bunnyidleCallback(void);    //idlecallback for bunny
        static void dragonidleCallback();      //idlecallback for dragon
        static void robotidleCallback();
        static void houseidleCallback();
        static void reshapeCallback(int, int);
        static void displayCallback(void);
        static void processNormalKeys(unsigned char key, int x, int y);
        static void processSpecialKeys(int key, int x, int y);
};

#endif

