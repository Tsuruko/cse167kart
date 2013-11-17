//
//  Camera.h
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#ifndef __cse167p6__Camera__
#define __cse167p6__Camera__

#include "Matrix4.h"
#include "Vector3.h"

class Camera{
private:
  Vector3 e;
  Vector3 d;
  Vector3 up;
  
  void generateMatrix();
  
public:
  Matrix4 c;
  Matrix4 cInv;
  
  Camera();
  Camera(const Vector3 &, const Vector3 &, const Vector3 &);
  GLfloat* getPointer() {return c.getPointer();}
  GLfloat* getInvPointer() {return cInv.getPointer();}
  Matrix4& getMatrix() {return c;}
};

#endif /* defined(__cse167p6__Camera__) */
