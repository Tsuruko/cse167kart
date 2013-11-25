//
//  Camera.h
//  cse167p6
//
//  Nick Troast, Monica Liu, Andrew Lin
//

#ifndef __cse167p6__Camera__
#define __cse167p6__Camera__

#include "Vector3.h"

class Camera{
private:
  Vector3 e;
  Vector3 d;
  Vector3 up;
  
public:
  Camera();
  Camera(Vector3, Vector3, Vector3);
  
};

#endif /* defined(__cse167p6__Camera__) */
