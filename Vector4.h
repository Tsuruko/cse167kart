//
//  Vector4.h
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#ifndef __cse167p6__Vector4__
#define __cse167p6__Vector4__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Vector4
{
protected:
  GLfloat v[4];
  
public:
  Vector4();
  Vector4(GLfloat, GLfloat, GLfloat, GLfloat);
  GLfloat& operator[](int);
  void dehomogenize();
  void print();
};

#endif /* defined(__cse167p6__Vector4__) */