#ifndef _GEODE_H_
#define _GEODE_H_

#include <GLUT/glut.h>
#include <cstring>
#include "Matrix4.h"

class geode {
  private:
//    virtual void boundingBox() = 0;

  public: 
    Vector3 trans;
    double r;
    virtual void draw() = 0;
};

#endif
