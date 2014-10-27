#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GLUT/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "main.h"

using namespace std;

namespace Globals
{
  Cube cube;
  class ball ball;
};

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
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
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  // register callbacks
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
    
  // Initialize cube matrix:
  Globals::cube.getMatrix().identity();
  
  // keyboard key
  glutKeyboardFunc(Window::processNormalKeys);


  //Test for Vector3 class
  Vector3 *vec3 = new Vector3(1.5,2,3);
  vec3->print("Vector3 information : ");
  
  Vector3 *vec3_add = new Vector3(1,2.5,2);
  *vec3 = *vec3 + *vec3_add;
  vec3->print("Vector3 addition : ");
    
  *vec3_add = *vec3 - *vec3_add;
  vec3_add->print("Vector3 substraction 1.5 2 3 : ");
    
  vec3->negate();
  vec3->print("Vector3 negation : -2.5 -4.5 -5 : ");
    
  vec3->scale(-3.0);
  vec3->print("Vector3 scaling : 7.5 13.5 15: ");
    
  double dot_product = vec3->dot(*vec3,*vec3_add);
  cout << "dot product result is 83.25 " << dot_product << endl;
    
  Vector3 cross_product = vec3->cross(*vec3, *vec3_add);
  cross_product.print("Cross product result should be 10.5 0 -5.25): ");
  vec3->print("vec3 info : 7.5 13.5 15: ");
  vec3_add->print("vec3_add info: 1.5 2 3 : ");
    
  double len = vec3->length();
  cout << "length of vec3 is 21.5291 " << len <<endl;

  vec3->normalize();
  cout << "length of vec3 after normalization is 1 " << vec3->length() << endl;
    
  //Test for Vector4 class
  Vector4 *vec1 = new Vector4(-1,1,0,2);
  Vector4 *vec2 = new Vector4(3,4,5,6);
  Vector4 vec_addition = *vec1 + *vec2;
  vec_addition.print("Vector4 addition is 2 5 5 8 : ");
  Vector4 vec_subtraction = *vec2 - *vec1;
  vec_subtraction.print("Vector4 subtraction is 4 3 5 4 : ");
  vec1->dehomogenize();
  vec1->print("vec1 after dehomogenize: -0.5 0.5 0 1: ");
  vec2-> dehomogenize();
  vec2->print("vec2 after dehomogenize: 0.5 2/3 5/6 1 : ");
    
  //Enter GLUT event processing cycle
  glutMainLoop();

    
  return 0;
}

