//
//  BCurve.h
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#ifndef __cse167p6__BCurve__
#define __cse167p6__BCurve__

#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"

class BCurve {
private:
  Vector3 cp[4];
  
public:
  BCurve();
  BCurve(Vector3, Vector3, Vector3, Vector3);
  Vector3 getPoint(GLfloat);
  Vector3 getTangent(GLfloat);
  GLfloat* getCPointer(int);
  Vector3& getCP(int);
  void setCP(int, int, GLfloat);
  BCurve rotateY(GLfloat angle);
};

#endif /* defined(__cse167p6__BCurve__) */