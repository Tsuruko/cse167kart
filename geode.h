//
//  geode.h
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 12/6/13
//
//  Modified: 12/7/13
//

#ifndef _GEODE_H_
#define _GEODE_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <cstdlib>
#include <GL/glut.h>
#endif
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
