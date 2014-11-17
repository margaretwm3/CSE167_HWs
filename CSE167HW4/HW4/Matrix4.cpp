#include <math.h>

#include "Matrix4.h"
#include <iostream>

using namespace std;

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
}

Matrix4::Matrix4(Vector3& a, Vector3& b, Vector3& c, Vector3& e,double x,double y,double z,double w){
   //row major ordering
    m[0][0] = a.x;
    m[1][0] = a.y;
    m[2][0] = a.z;
    m[3][0] = x;
    
    m[0][1] = b.x;
    m[1][1] = b.y;
    m[2][1] = b.z;
    m[3][1] = y;

    m[0][2] = c.x;
    m[1][2] = c.y;
    m[2][2] = c.z;
    m[3][2] = z;
    
    m[0][3] = e.x;
    m[1][3] = e.y;
    m[2][3] = e.z;
    m[3][3] = w;
}

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}


//multiply matrix with matrix
Matrix4 Matrix4::operator*(const Matrix4& m2){
    Matrix4* product = new Matrix4();
    for(int row = 0; row < 4; row ++){
        for(int col = 0; col < 4; col++){
            for(int inner = 0; inner < 4; inner++){
                product->m[row][col] += this->m[row][inner]*m2.m[inner][col];
            }
        }
    }
    return *product;
 }

//multiply matrix with vector
Vector4 Matrix4::operator*(const Vector4& v){
    double res1 = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
    double res2 = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
    double res3 = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
    double res4 = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
    Vector4 *result = new Vector4(res1,res2,res3,res4);
    return *result;
}

//make rotation matrix about X axis with angle in degrees (note that the sin/cos functions in C++ expect radians so you need to convert to radians within the function
void Matrix4::makeRotateX(double angle){
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
    identity();
    m[1][1] = cos(angle);
    m[2][1] = sin(angle);
    m[1][2] = -sin(angle);
    m[2][2] = cos(angle);
}

//make rotation matrix about Z axis with angle in degrees
void Matrix4::makeRotateZ(double angle){
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
    identity();
    m[0][0] = cos(angle);
    m[1][0] = sin(angle);
    m[0][1] = -sin(angle);
    m[1][1] = cos(angle);
}

//Make a rotation matrix about an arbitrary axis
void Matrix4::makeRotate(double angle, const Vector3& axis){
  //transform the axis to be a unit vector
  Vector3 normalized = axis;
  normalized.normalize();
  angle = angle/180.0 * M_PI;
  identity();
  m[0][0] = cos(angle) +   normalized.x * normalized.x * (1-cos(angle));
  m[0][1] = normalized.x * normalized.y *(1-cos(angle)) -  normalized.z * sin(angle);
  m[0][2] = normalized.x * normalized.z * (1-cos(angle)) + normalized.y * sin(angle);
  m[1][0] = normalized.y * normalized.x * (1-cos(angle)) + normalized.z * sin(angle);
  m[1][1] = cos(angle) + normalized.y * normalized.y * (1-cos(angle));
  m[1][2] = normalized.y * normalized.z * (1-cos(angle)) - normalized.x * sin(angle);
  m[2][0] = normalized.z * normalized.x * (1-cos(angle)) - normalized.y * sin(angle);
  m[2][1] = normalized.z * normalized.y * (1-cos(angle)) + normalized.x * sin(angle);
  m[2][2] = cos(angle) + normalized.z * normalized.z * (1-cos(angle));
}

//make a non-uniform scaling matrix
void Matrix4::makeScale(double sx, double sy, double sz){
    identity();
    this->m[0][0] = this->m[0][0] * sx;
    this->m[0][1] = this->m[0][1] * sx;
    this->m[0][2] = this->m[0][2] * sx;
    
    this->m[1][0] = this->m[1][0] * sy;
    this->m[1][1] = this->m[1][1] * sy;
    this->m[1][2] = this->m[1][2] * sy;
    
    this->m[2][0] = this->m[2][0] * sz;
    this->m[2][1] = this->m[2][1] * sz;
    this->m[2][2] = this->m[2][2] * sz;
}

//make a translation matrix
void Matrix4::makeTranslate(double tx, double ty, double tz){
    identity();
    this->m[0][3] = tx;
    this->m[1][3] = ty;
    this->m[2][3] = tz;
}

//print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)
void Matrix4::print(string comment){
  cout << comment
    << "[" << " " << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << "\n"
                  << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << "\n"
                  << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << "\n"
    << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << "\n" << "]" << endl;

}


