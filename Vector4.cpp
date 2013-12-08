//
//  Vector4.cpp
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 11/17/13
//
//  Modified: 12/7/13
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include "Vector4.h"

Vector4::Vector4() {
  for (int i=0; i<4; ++i) {
    v[i] = 0;
  }
}

Vector4::Vector4(float x, float y, float z, float w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

float& Vector4::operator[](int i)
{
	return v[i];
}

void Vector4::dehomogenize()
{
  v[0] /= v[3];
  v[1] /= v[3];
  v[2] /= v[3];
  v[3] = 1;
}

void Vector4::print()
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << std::setw(6) << std::fixed << std::setprecision(2) << v[i];
	}
	std::cout << std::endl << std::endl;
}

double Vector4::dot(Vector4 B) {
  return ( (v[0] * B[0]) + (v[1] * B[1]) + (v[2] * B[2]) + (v[3] * B[3]) );
}

Vector4 Vector4::scale(GLfloat s)
{
  return Vector4(v[0] * s,
                 v[1] * s,
                 v[2] * s,
				 v[2] * s);
}
