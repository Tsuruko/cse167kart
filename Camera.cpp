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
  eye_t = 0;
  center_t = 0.2;
  eyeCurve = centerCurve = 0;
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
  this->e[2] = this->e[2] + 0.4; // Move the eye to the 3rd person
}

void Camera::setUp(Vector3 up)
{
  this->up = up;
}

Matrix4 Camera::generateMatrix()
{
  Vector3 xAxis, yAxis, zAxis;
  GLfloat magnitude;
  Matrix4 c, cInv;
  
  zAxis = e - d;
  magnitude = zAxis.magnitude();
  zAxis[0] = zAxis[0] / magnitude;
  zAxis[1] = zAxis[1] / magnitude;
  zAxis[2] = zAxis[2] / magnitude;
  
  xAxis = Vector3::cross(up, zAxis);
  magnitude = xAxis.magnitude();
  xAxis[0] = xAxis[0] / magnitude;
  xAxis[1] = xAxis[1] / magnitude;
  xAxis[2] = xAxis[2] / magnitude;
  
  yAxis = Vector3::cross(zAxis, xAxis);
  
  c = Matrix4(xAxis[0], yAxis[0], zAxis[0], e[0],
              xAxis[1], yAxis[1], zAxis[1], e[1],
              xAxis[2], yAxis[2], zAxis[2], e[2],
              0, 0, 0, 1);
  
  Matrix4 r = Matrix4(xAxis[0], yAxis[0], zAxis[0], 0,
                      xAxis[1], yAxis[1], zAxis[1], 0,
                      xAxis[2], yAxis[2], zAxis[2], 0,
                      0, 0, 0, 1);
  
  //r.transpose();
  
  Matrix4 t = Matrix4(1, 0, 0, -e[0],
                      0, 1, 0, -e[1],
                      0, 0, 1, -e[2],
                      0, 0, 0, 1);
  
  cInv = r * t;
  
  return cInv;
}
