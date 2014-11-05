#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#define M_PI 3.14159265358979323846
#include "Vector4.h"
#include "Vector3.h"


class Matrix4
{
  protected:
    double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)
    
  public:
    Matrix4();
    Matrix4(Vector3& a, Vector3& b, Vector3& c,Vector3& e,double x,double y,double z,double w);
    Matrix4& operator=(const Matrix4&);
    double* getPointer(); 
    void identity(); 
    void transpose();
    void makeRotateY(double);
    
    Matrix4 operator*(const Matrix4& m2);
    Vector4 operator*(const Vector4& v);
    void makeRotateX(double angle);
    void makeRotateZ(double angle);
    void makeRotate(double angle, const Vector3& axis);
    void makeScale(double sx, double sy, double sz);
    void makeTranslate(double tx, double ty, double tz);
    void print(string comment);
    void makeProjectionMatrix(double fov, double aspect_ratio,double near, double far);
    void makeViewportMatrix(double x0,double x1,double y0,double y1);
    friend class Camera;
   
};

#endif