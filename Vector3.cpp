//
//  Vector3.cpp
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include "Vector3.h"

Vector3::Vector3()
{
  v[0] = 0;
  v[1] = 0;
  v[2] = 0;
}

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z)
{
  v[0] = x;
  v[1] = y;
  v[2] = z;
}

float& Vector3::operator[](int i)
{
	return v[i];
}

Vector3 Vector3::operator+(Vector3& rhs)
{
  return Vector3(v[0] + rhs[0],
                 v[1] + rhs[1],
                 v[2] + rhs[2]);
}

Vector3 Vector3::operator-(Vector3& rhs)
{
  return Vector3(v[0] - rhs[0],
                 v[1] - rhs[1],
                 v[2] - rhs[2]);
}

Vector3 Vector3::scale(GLfloat s)
{
  return Vector3(v[0] * s,
                 v[1] * s,
                 v[2] * s);
}

Vector3 Vector3::cross(Vector3& A, Vector3& B)
{
  return Vector3(A[2] * B[3] - A[3] * B[2],
                 A[2] * B[3] - A[3] * B[2],
                 A[2] * B[3] - A[3] * B[2]);
}

GLfloat Vector3::magnitude()
{
  return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void Vector3::normalize()
{
  GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
  if (d != 0.0)
  {
    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
  }
}

