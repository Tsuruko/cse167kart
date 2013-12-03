#ifndef _CAR_H_
#define _CAR_H_

#include "objreader.h"
#include "Matrix4.h"

class car {

  public:
    float material[3];

    Matrix4 scale;
    Matrix4 trans;

    int nVerts; 
    float *vertices; 
    float *normals; 
    float *texcoords; 
    int nIndices; 
    int *indices; 

    car();
    void draw(Matrix4);
};


#endif
