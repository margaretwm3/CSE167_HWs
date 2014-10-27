#include "Cube.h"
#include "Matrix4.h"
#include <iostream>

using namespace std;

Cube::Cube()
{
  angle = 0.0;
  position = new Vector4(0.0,0.0,0.0,1.0);
}

Matrix4& Cube::getMatrix()
{
  return model2world;
}

void Cube::spin(double deg)   // deg is in degrees
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  //Vector3 *axis = new Vector3(1,0,0);
    Matrix4 tmp = Matrix4();
    tmp.makeRotateY(deg);
    model2world = model2world*tmp;
   /* This does not move left because it always calls identity() */
  //model2world.makeRotateY(angle);   // This creates the matrix to rotate the cube
}

void Cube::moveLeft(){
    //create a translation matrix
    Matrix4 *tmp = new Matrix4();
    tmp->makeTranslate(-1.0,0,0);
    model2world = *tmp * model2world;
    //update the Vector4 postion vector
    *position = *tmp * *position;
}

void Cube::moveRight(){
    //create a translation matrix
    Matrix4 *tmp = new Matrix4();
    tmp->makeTranslate(1.0,0.0,0.0);
    model2world = *tmp * model2world;
    //update the Vector4 postion vector
    *position = *tmp * *position;
}

void Cube::moveDown(){
    //Create a translation Matrix
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0.0,-1.0,0.0);
    model2world = tmp * model2world;
    //update the Vector4 postion vector
    *position = tmp * *position;
}

void Cube::moveUp(){
    //Create a translation Matrix
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0.0,1.0,0.0);
    model2world = tmp * model2world;
    //update the Vector4 postion vector
    *position = tmp * *position;
}

void Cube::moveInto(){
    //Create a translation Matrix
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0.0,0.0,1.0);
    model2world = tmp * model2world;
    //update the Vector4 postion vector
    *position = tmp * *position;

}
void Cube::moveOutOf(){
    //Create a translation Matrix
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0.0,0.0,-1.0);
    //The multiplication order is important
    model2world = tmp * model2world;
    //update the Vector4 postion vector
    *position = tmp * *position;
}

//reset cube position, orientation, size and color
void Cube::reset(){
    model2world.identity();
    position = new Vector4(0.0, 0.0, 0.0, 1.0);
}

//it can orbit clockwise or counterclockwise
void Cube::orbit(int direction){
    //rotate around the z-axis, make rotation matrix
    Matrix4 rotationMatrix = Matrix4();
    rotationMatrix.makeRotateZ(direction * 10);
    model2world = rotationMatrix * model2world;
    *position = rotationMatrix * *position;
}

void Cube::scale(double scale){
    Matrix4 tmp = Matrix4();
    //tmp.identity();
    tmp.makeScale(scale, scale, scale);
    // the order is important to keep in the local space
    model2world = model2world * tmp;
    *position = tmp * *position;
}



