
#include <stdio.h>
#include "object.h"

object::object() {
  objName = "";
  tf.identity();
  inv.identity();
  scale.set(1,1,1,1);
  translate.set(0,0,0,1);
  xmax = ymax = zmax = xmin = ymin = zmin = 0;
  material[0] = material[1] = material[2] = 0.0;
}

void object::setName(const char* name) {
  objName = name;
}

void object::minMax() {
    int j = 0;
    for (int i = 0; i < nVerts; i++) {
        j = i * 3;
        if (vertices[j] > xmax) {
            xmax = vertices[j];
        } else if (vertices[j] < xmin) {   
	    xmin = vertices[j];
        }

	if (vertices[j+1] > ymax) {
	    ymax = vertices[j+1];
	} else if (vertices[j+1] < ymin) {
	    ymin = vertices[j+1];
	}

	if (vertices[j+2] > zmax) {
	    zmax = vertices[j+2];
	} else if (vertices[j+2] < zmin) {
	    zmin = vertices[j+2];
	} 
    }
}

void object::printVert() {
    printf("x min,max: {%g,%g}\n", xmin, xmax);
    printf("y min,max: {%g,%g}\n", ymin, ymax);
    printf("z min,max: {%g,%g}\n", zmin, zmax);
}
