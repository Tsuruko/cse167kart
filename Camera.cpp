//
//  Camera.cpp
//  cse167p6
//
//  Nick Troast, Monica Liu, Andrew Lin
//

#include "Camera.h"

Camera::Camera(Vector3 e, Vector3 d, Vector3 up)
{
  this->e = e;
  this->d = d;
  this->up = up;
}

Vector3& Camera::getCenter()
{
  return d;
}

Vector3& Camera::getEye()
{
  return e;
}

Vector3& Camera::getUp()
{
  return up;
}

void Camera::setCenter(GLfloat x, GLfloat y, GLfloat z)
{
  d[0] = x;
  d[1] = y;
  d[2] = z;
}

void Camera::setEye(GLfloat x, GLfloat y, GLfloat z)
{
  e[0] = x;
  e[1] = y;
  e[2] = z;
}

void Camera::setUp(GLfloat x, GLfloat y, GLfloat z)
{
  up[0] = x;
  up[1] = y;
  up[2] = z;
}

void Camera::setCenter(Vector3 d)
{
  this->d = d;
}

void Camera::setEye(Vector3 e)
{
  this->e = e;
  e[2] = e[2] + 1; // Move the eye to the 3rd person
}

void Camera::setUp(Vector3 up)
{
  this->up = up;
}