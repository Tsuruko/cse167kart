#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Matrix4.h"

class sphere {
  private:
    double r;
    Matrix4 center;    //adjust the center to the bottom of the sphere
  public:
    sphere (double radius) {
      r = radius;
    }

  public draw(Matrix4 C) {
    glMatrixMode(GL_MODELVIEW);
    glutSolidSPhere(r, 10.0, 10.0);
  }
