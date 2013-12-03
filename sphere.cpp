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
      r = radius; ///10.0;
      center = Matrix4::translate(-2.5, 5.0, 4.0);
   }

  void draw(Matrix4 C) {
    glMatrixMode(GL_MODELVIEW);
    Matrix4 pos = center * C;
    glLoadMatrixf(pos.getPointer());
    glutSolidSphere(r, 10.0, 10.0);
  }

};
