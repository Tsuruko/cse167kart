//
//  sphere.cpp
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 12/2/13
//
//  Modified: 12/7/13
//

#include "geode.h"

class sphere : public geode {
  private:void calculateBoundingSphere() {
    GLdouble modelview[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

    bounding = Vector4(modelview[12], modelview[13], modelview[14], 1);
  }

  public: sphere(float radius, Vector3 pos) {
    trans = pos;
    r = radius;
  }

  public: void draw() {
    glTranslatef(trans[0], trans[1], trans[2]+r);   
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(r, 10.0, 10.0);
    calculateBoundingSphere();
    glTranslatef(-trans[0], -trans[1], -(trans[2]+r));
  }

  public: Vector4 getBoundingSphere() {
    return bounding;
  }

  public:void updateLoc(Vector3 temp){
    trans = temp;
  }
};
