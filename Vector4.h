//
//  Vector4.h
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 11/17/13
//
//  Modified: 12/7/13
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
  double dot(Vector4 B);
  Vector4 scale(GLfloat);
};

#endif /* defined(__cse167p6__Vector4__) */
