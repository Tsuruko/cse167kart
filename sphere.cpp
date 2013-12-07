#include "geode.h"

class sphere : public geode {

  public:sphere(double radius, Vector3 pos) {
    trans = Matrix4::translate(pos[0]*1.0, pos[1]*1.0, (pos[2]*1.0)+radius);
    r = radius;
  }

  public:void draw(Matrix4 C) {
      glMatrixMode(GL_MODELVIEW);
      Matrix4 Cnew = trans * C;
      glLoadMatrixf(Cnew.getPointer());
   
      glutSolidSphere(r, 10.0, 10.0);
      //glLoadMatrixf(C.getPointer());
  }
};
