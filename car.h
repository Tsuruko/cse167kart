#ifndef _CAR_H_
#define _CAR_H_


#include "FireCone.h"

class car {
  
private:
  GLfloat xpos, zpos;
  Matrix4 firetrans1, firetrans2;
  Vector3 scale;
  Vector3 forwardTrans, sideTrans;
  Vector3 prevT;
  float angle;
  float xmin, xmax, ymin, ymax, zmin, zmax;
  FireCone *fire1, *fire2;
  
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
  void draw(Matrix4, Matrix4);
  void moveSide(GLfloat);
  void moveForward(Vector3);
  void findMinMax();
};

#endif
