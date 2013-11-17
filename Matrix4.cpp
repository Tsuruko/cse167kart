//
//  Matrix4.cpp
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include "Matrix4.h"

Matrix4::Matrix4()
{
  GLfloat ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

Matrix4::Matrix4(GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
                 GLfloat m10, GLfloat m11, GLfloat m12, GLfloat m13,
                 GLfloat m20, GLfloat m21, GLfloat m22, GLfloat m23,
                 GLfloat m30, GLfloat m31, GLfloat m32, GLfloat m33)
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

GLfloat* Matrix4::getPointer()
{
  return &m[0][0];
}

void Matrix4::identity()
{
  *this = Matrix4();
}

void Matrix4::transpose()
{
	GLfloat temp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			temp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = temp;
		}
	}
}

Matrix4 Matrix4::operator*(Matrix4& other)
{
	Matrix4 temp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				temp[i][j] += m[i][k] * other[k][j];
			}
		}
	}
  return temp;
}

Vector4 Matrix4::operator*(Vector4& other)
{
  Vector4 temp;
	for (int i = 0; i < 4; i++)
	{
    temp[i] = 0;
		for (int j = 0; j < 4; j++)
		{
      temp[i] += m[i][j] * other[j];
		}
	}
  return temp;
}

Matrix4 Matrix4::translate(GLfloat x, GLfloat y, GLfloat z)
{
	return Matrix4(1.0, 0.0, 0.0, x,
                 0.0, 1.0, 0.0, y,
                 0.0, 0.0, 1.0, z,
                 0.0, 0.0, 0.0, 1.0);
}

Matrix4 Matrix4::scale(GLfloat x, GLfloat y, GLfloat z)
{
	return Matrix4(x, 0.0, 0.0, 0.0,
                 0.0, y, 0.0, 0.0,
                 0.0, 0.0, z, 0.0,
                 0.0, 0.0, 0.0, 1.0);
}

Matrix4 Matrix4::rotate(GLfloat angle, Vector3 &u)
{
	return Matrix4(1 + (1 - cos(angle)) * ((u[0] * u[0]) - 1),
                 -u[2] * sin(angle) + (1 - cos(angle)) * u[0] * u[1],
                 u[1] * sin(angle) + (1 - cos(angle)) * u[0] * u[2], 0.0,
                 u[2] * sin(angle) + (1 - cos(angle)) * u[1] * u[0],
                 1 + (1 - cos(angle)) * ((u[1] * u[1]) - 1),
                 -u[0] * sin(angle) + (1 - cos(angle)) * u[1] * u[2], 0.0,
                 -u[1] * sin(angle) + (1 - cos(angle)) * u[2] * u[0],
                 u[0] * sin(angle) + (1 - cos(angle)) * u[2] * u[1],
                 1 + (1 - cos(angle)) * ((u[2] * u[2]) - 1), 0.0,
                 0.0, 0.0, 0.0, 1.0);
}

Matrix4 Matrix4::rotateY(GLfloat angle)
{
  angle = angle * (M_PI/180); // convert to radians
  return Matrix4(cos(angle), 0, sin(angle), 0,
                 0, 1, 0, 0,
                 -sin(angle), 0, cos(angle), 0,
                 0, 0, 0, 1);
}

void Matrix4::print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << std::setw(6) << std::fixed << std::setprecision(2) << m[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
