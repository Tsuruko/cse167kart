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

  private:void calculateBoundingSphere() {
    GLdouble modelview[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    bounding = Vector4(modelview[12], modelview[13], modelview[14], 1);
  }

  public:cube(float side, Vector3 pos) {
    trans = pos;
    s = side;
    r = std::sqrt(2*std::pow(s, 2))/2;
  }

  public:void draw() {
    glTranslatef(trans[0], trans[1], trans[2]+r);   
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(s);
    calculateBoundingSphere();
    glTranslatef(-trans[0], -trans[1], -(trans[2]+r));
  }

  public: Vector4 getBoundingSphere() {
    return bounding;
  }
};
