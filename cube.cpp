#include "geode.h"

class cube : public geode {
  public:cube(double radius, Vector3 pos) {
    trans = pos;
    r = radius;
  }

  public:void draw() {
      glTranslatef(trans[0], trans[1], trans[2]+r);   
      glColor3f(1.0, 0.0, 0.0);
      glutSolidCube(r*2);
      glTranslatef(-trans[0], -trans[1], -(trans[2]+r));
  }
};
