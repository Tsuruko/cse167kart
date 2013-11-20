//
//  Vector3.cpp
//  cse167p6
//
//  Nick Troast, Monica Liu, Andrew Lin
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

Vector3 Vector3::cross(Vector3 c) {
  double nx = ( (v[1] * c[2]) - (v[2] * c[1]));
  double ny = ( (v[2] * c[0]) - (v[0] * c[2]));
  double nz = ( (v[0] * c[1]) - (v[1] * c[0]));
  v[0] = nx;
  v[1] = ny;
  v[2] = nz;
  return *this;
}

GLfloat Vector3::magnitude()
{
  return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void Vector3::normalize()
{
  GLfloat d = this->magnitude();
  if (d != 0.0)
  {
    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
  }
}

double Vector3::dot(Vector3 B) {
  return ( (v[0] * B[0]) + (v[1] * B[1]) + (v[2] * B[2]) );
}

GLfloat Vector3::angle(Vector3 v2) {
  double dot = this->dot(v2);
  GLfloat mag = magnitude(); 
  GLfloat magv = v2.magnitude();
  GLfloat cos = dot/(mag*magv);
  GLfloat ang = acos(cos);
  return ang;
}

