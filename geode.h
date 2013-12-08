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

#include "Matrix4.h"

class geode {
  public: 
    Vector3 trans;
    float r;
    virtual void draw() = 0;
    virtual Vector4 getBoundingSphere() = 0;
};

#endif
