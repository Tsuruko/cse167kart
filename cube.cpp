//
//  cube.cpp
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 12/6/13
//
//  Modified: 12/7/13
//

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
