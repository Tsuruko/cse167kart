//
//  BCurve.cpp
//  cse167p6
//
//  Created by Nick Troast on 11/12/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#include "BCurve.h"

BCurve::BCurve()
{
  for (int i = 0; i < 4; i++)
    cp[i] = Vector3();
}

BCurve::BCurve(Vector3 cp0, Vector3 cp1, Vector3 cp2, Vector3 cp3)
{
  cp[0] = cp0;
  cp[1] = cp1;
  cp[2] = cp2;
  cp[3] = cp3;
}

GLfloat* BCurve::getCPointer(int p)
{
  Vector3 temp = Vector3(cp[p][0], cp[p][1], -3.5);
  return temp.getPointer();
}

Vector3& BCurve::getCP(int p)
{
  return cp[p];
}

void BCurve::setCP(int i, int j, GLfloat n)
{
  cp[i][j] = n;
}

Vector3 BCurve::getPoint(GLfloat t)
{
  Vector3 temp[4];
  temp[0] = cp[0].scale((1 - t) * (1 - t) * (1 - t));
  temp[1] = cp[1].scale(3 * (1 - t) * (1 - t) * t);
  temp[2] = cp[2].scale(3 * (1 - t) * t * t);
  temp[3] = cp[3].scale(t * t * t);
  return (temp[0] + temp[1] + temp[2] + temp[3]);
}

Vector3 BCurve::getTangent(GLfloat t)
{
  Vector3 temp[6];
  temp[0] = cp[0].scale(-3 * (1 - t) * (1 - t));
  temp[1] = cp[1].scale(3 * (1 - t) * (1 - t));
  temp[2] = cp[1].scale(-6 * t * (1 - t));
  temp[3] = cp[2].scale(-3 * t * t);
  temp[4] = cp[2].scale(6 * t * (1 - t));
  temp[5] = cp[3].scale(3 * t * t);
  return (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5]);
}