//
//  Camera.cpp
//  cse167p6
//
//  Nick Troast, Monica Liu, Andrew Lin
//

#include "Camera.h"

Camera::Camera(const Vector3& e, const Vector3& d, const Vector3& up)
{
  this->e = e;
  this->d = d;
  this->up = up;
  generateMatrix();
}

void Camera::generateMatrix()
{
  Vector3 xAxis, yAxis, zAxis;
  GLfloat magnitude;
  
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
  
  r.transpose();
  
  Matrix4 t = Matrix4(1, 0, 0, -e[0],
                      0, 1, 0, -e[1],
                      0, 0, 1, -e[2],
                      0, 0, 0, 1);
  
  cInv = r * t;
}