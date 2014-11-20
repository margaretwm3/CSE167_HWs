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
        static void reshapeCallback(int, int);
        static void displayCallback(void);
        static void processNormalKeys(unsigned char key, int x, int y);
        static void processSpecialKeys(int key, int x, int y);
        static void onMouseClick(int button, int state, int x, int y);
        static Vector3 trackBallMapping( int x, int y );
        static void motionCallback(int x, int y);

    
        //for dragon
        static void idleDragonCallback(void);    //idlecallback for bunny
        static void displayDragonCallback(void);
        static void processDragonNormalKeys(unsigned char key, int x, int y);
    
        //for bunny
        static void displayBunnyCallback(void);
        static void idleBunnyCallback(void);    //idlecallback for bunny
        static void processBunnyNormalKeys(unsigned char key, int x, int y);
    
        //for bear
        static void displayBearCallback(void);
        static void idleBearCallback(void);    //idlecallback for bunny
        static void processBearNormalKeys(unsigned char key, int x, int y);
    
};

#endif

