//
//  car.h
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 12/2/13
//
//  Modified: 12/7/13
//

#ifndef _CAR_H_
#define _CAR_H_


#include "FireCone.h"

class car {
  
private:

//moving the car:
  GLfloat xpos, zpos;   
  Vector3 forwardTrans, sideTrans, prevT; 
  float scale;

  float xmin, xmax, ymin, ymax, zmin, zmax;   //find size of the car
  float r;   //bounding box radius
  FireCone *fire;

  float getRadius();
  
public:
//traversing the track
  GLfloat t;
  int curve;

//reading in object
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
  Vector4 getBoundingSphere();
};

#endif
