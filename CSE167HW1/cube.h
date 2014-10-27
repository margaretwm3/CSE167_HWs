#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"
#include "Vector4.h"

class Cube
{
  protected:
    Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
    double angle;                   // rotation angle [degrees]
    Vector4 *position;

  public:
    Cube();   // Constructor
    Matrix4& getMatrix();
    void spin(double);      // spin cube [degrees]
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    void moveInto();
    void moveOutOf();
    void reset();
    void orbit(int direction);
    void scale(double scale);
    friend class Window;
};

#endif

