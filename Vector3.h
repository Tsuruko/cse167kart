//
//  Vector3.h
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 11/17/13
//
//  Modified: 12/7/13
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
  void set(GLfloat, GLfloat, GLfloat);
  GLfloat* getPointer() {return &v[0];};
  GLfloat& operator[](int);
  Vector3 operator-(Vector3&);
  Vector3 operator+(Vector3&);
  Vector3 scale(GLfloat);
  static Vector3 cross(Vector3&, Vector3&);
  Vector3 cross(Vector3);
  GLfloat magnitude();
  void normalize();
  double dot(Vector3);
  GLfloat  angle(Vector3);
};

#endif /* defined(__cse167p6__Vector3__) */
