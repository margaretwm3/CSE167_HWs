#ifndef _MAIN_H_
#define _MAIN_H_


#include "Camera.h"
#include "Robot.h"
#include "MatrixTransform.h"

namespace Globals
{
    extern Camera camera;
    extern Robot robot;
    extern bool boundingBox;
    extern MatrixTransform root;
};

#endif