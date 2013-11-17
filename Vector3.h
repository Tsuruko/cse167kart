//
//  Vector3.h
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#ifndef __cse167p6__Vector3__
#define __cse167p6__Vector3__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Vector3 {
private:
  GLfloat v[3];
  
public:
  Vector3();
  Vector3(GLfloat, GLfloat, GLfloat);
  GLfloat* getPointer() {return &v[0];};
  GLfloat& operator[](int);
  Vector3 operator-(Vector3&);
  Vector3 operator+(Vector3&);
  Vector3 scale(GLfloat);
  static Vector3 cross(Vector3&, Vector3&);
  GLfloat magnitude();
  void normalize();
};

#endif /* defined(__cse167p6__Vector3__) */
