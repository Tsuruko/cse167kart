//
//  FireCone.h
//  FireCone
//
//  Created by Nick Troast on 12/2/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#ifndef __FireCone__FireCone__
#define __FireCone__FireCone__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "Vector3.h"
#include "Matrix4.h"
#define PI 3.14159265

class Particle
{
public:
  Vector3 v;
  GLint theta;
  Particle() {
    v[0] = 0;
    v[1] = 0;
    v[2] = (rand() % 100) / 100.0;
    theta = rand() % 360;
  }
};

class FireCone
{
private:
  std::vector<Particle> particles;
public:
  Matrix4 scale;
  FireCone();
  void draw();
};

#endif /* defined(__FireCone__FireCone__) */
