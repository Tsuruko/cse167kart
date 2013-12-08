//
//  cube.cpp
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 12/6/13
//
//  Modified: 12/7/13
//

#include <cmath>
#include "geode.h"

class cube : public geode {
  private: float s;

  public:cube(float side, Vector3 pos) {
    trans = pos;
    s = side;
    r = std::sqrt(2*std::pow(s, 2))/2;
  }

  public:void draw() {
      glTranslatef(trans[0], trans[1], trans[2]+r);   
      glColor3f(1.0, 0.0, 0.0);
      glutSolidCube(s);
      glTranslatef(-trans[0], -trans[1], -(trans[2]+r));
  }
};
