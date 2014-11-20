#ifndef _MAIN_H_
#define _MAIN_H_


#include "Camera.h"
#include "Robot.h"
#include "bunny.h"
#include "dragon.h"
#include "bear.h"
#include "shader.h"
#include "MatrixTransform.h"
#include "Light.h"

namespace Globals
{
    extern Camera camera;
    extern Robot robot;
    extern bool boundingBox;
    extern MatrixTransform root;
    extern bunny *bunny;
    extern dragon *dragon;
    extern bear *bear;
    extern Shader *shader;
};

#endif