#ifndef _CAR_H_
#define _CAR_H_


#include "FireCone.h"

class car {
  
private:
  GLfloat xpos, zpos;
  Vector3 forwardTrans, sideTrans;
  Vector3 prevT;
  float scale;
  float xmin, xmax, ymin, ymax, zmin, zmax;
  FireCone *fire;
  
public:
  GLfloat t;
  int curve;
  int nVerts;
  float *vertices;
  float *normals;
  float *texcoords;
  int nIndices;
  int *indices;
  car(float);
  void draw();
  void moveSide(GLfloat);
  void moveForward(Vector3);
  void findMinMax();
};

#endif
