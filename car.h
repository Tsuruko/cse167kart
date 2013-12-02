#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "objreader.h"
#include "Matrix4.h"

class object {

  public:
    double xmin;
    double ymin;
    double zmin;
    double xmax;
    double ymax;
    double zmax;

    float material[3];
    char mType;

    Matrix4 inv;
    Matrix4 tf;
    Vector4 scale;
    Vector4 translate;
    const char* objName;
    int nVerts; 
    float *vertices; 
    float *normals; 
    float *texcoords; 
    int nIndices; 
    int *indices; 
    object();
    void setName(const char*);
    void minMax();
    void printVert();
};


#endif
