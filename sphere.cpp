#include "geode.h"

class sphere : public geode {
  public:sphere(double radius, Vector3 pos) {
    trans = pos;
    r = radius;
  }

  public:void draw() {
      glTranslatef(trans[0], trans[1], trans[2]);   
      glutSolidSphere(r, 10.0, 10.0);
      glTranslatef(-trans[0], -trans[1], -trans[2]);
  }
};
