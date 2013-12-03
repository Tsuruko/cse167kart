#ifndef _CAR_H_
#define _CAR_H_

#include "Matrix4.h"

class car {

  private:
    GLfloat xpos;
    Matrix4 scale;
    Matrix4 trans;

  public:
    int nVerts; 
    float *vertices; 
    float *normals; 
    float *texcoords; 
    int nIndices; 
    int *indices; 

    car(float);
    void draw(Matrix4);
    void moveCar(GLfloat);
};

#endif
