//
//  Matrix4.h
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#ifndef __cse167p6__Matrix4__
#define __cse167p6__Matrix4__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Vector3.h"
#include "Vector4.h"

class Matrix4
{
private:
  GLfloat m[4][4];
  friend class Matrix4Row;
  GLfloat&   pget(int x,int y) { return m[x][y]; }
  
public:
  class Matrix4Row
  {
    Matrix4& parent;
    int x;
  public:
    Matrix4Row(Matrix4& p, int theX) : parent(p), x(theX) {}
    GLfloat& operator[](int y) const { return parent.pget(x,y); }
  };
  
  Matrix4();
  Matrix4(GLfloat, GLfloat, GLfloat, GLfloat,
          GLfloat, GLfloat, GLfloat, GLfloat,
          GLfloat, GLfloat, GLfloat, GLfloat,
          GLfloat, GLfloat, GLfloat, GLfloat);
  Matrix4Row operator[](int x) { return Matrix4Row(*this, x);}
  GLfloat* getPointer();
  void identity();
  void transpose();
  Matrix4 operator*(Matrix4&);
  Vector4 operator*(Vector4&);
  static Matrix4 translate(GLfloat, GLfloat, GLfloat);
  static Matrix4 scale(GLfloat, GLfloat, GLfloat);
  static Matrix4 rotate(GLfloat, Vector3&);
  static Matrix4 rotateY(GLfloat);
  void rotateX(GLfloat);
  Matrix4 trackballRotation(int, int, int, int, int, int);
  void print();
};

#endif /* defined(__cse167p6__Matrix4__) */
