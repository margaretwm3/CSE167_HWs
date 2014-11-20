#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GLUT/glut.h>

#include "Window.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "shader.h"
#include "bunny.h"
#include "main.h"
#include "bear.h"

using namespace std;

namespace Globals
{
  Camera camera;
  Robot robot = Robot();
  bool boundingBox = false;
  MatrixTransform root = MatrixTransform();
  class bunny *bunny;
  class dragon *dragon;
  class bear *bear;
  Shader* shader;
};


int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
    
  Globals::bunny = new bunny();
  Globals::dragon = new dragon();
  Globals::bear = new bear();

    
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube");    	      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION);
  
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glDisable(GL_LIGHTING); //turn the light off
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  
    
  // Install callback functions:
  // register callbacks
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

  // keyboard key
  glutKeyboardFunc(Window::processNormalKeys);
  glutSpecialFunc(Window::processSpecialKeys);

 //Enter GLUT event processing cycle
  glutMainLoop();
  
  return 0;
}

