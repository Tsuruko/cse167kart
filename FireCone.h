//
//  FireCone.h
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 12/4/13
//
//  Modified: 12/7/13
//

#ifndef __FireCone__FireCone__
#define __FireCone__FireCone__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "Vector3.h"
#include "Matrix4.h"
#include "core.h"

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
