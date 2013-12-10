//
//  Camera.h
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 11/17/13
//
//  Modified: 12/7/13
//

#ifndef __cse167p6__Camera__
#define __cse167p6__Camera__

#include "Vector3.h"
#include "Matrix4.h"

class Camera{
private:
  Vector3 e;
  Vector3 d;
  Vector3 up;
  
public:
  GLfloat eye_t, center_t;
  int eyeCurve, centerCurve;
  Camera();
  Camera(Vector3, Vector3, Vector3);
  Vector3& getEye();
  Vector3& getCenter();
  Vector3& getUp();
  void setEye(GLfloat, GLfloat, GLfloat);
  void setCenter(GLfloat, GLfloat, GLfloat);
  void setUp(GLfloat, GLfloat, GLfloat);
  void setEye(Vector3);
  void setCenter(Vector3);
  void setUp(Vector3);
  Matrix4 generateMatrix();
  void reset();
};

#endif /* defined(__cse167p6__Camera__) */
