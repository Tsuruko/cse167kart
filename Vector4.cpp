//
//  Vector4.cpp
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include "Vector4.h"

Vector4::Vector4()
{
	for (int i=0; i<4; ++i)
	{
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