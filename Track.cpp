//
//  Track.cpp
//  cse167kart
//
//  Created by Nick Troast on 11/17/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#include "Track.h"

Track::Track()
{
  curves.clear();
}

void Track::addCurve(BCurve * c) {
  curves.push_back(c);
}

void Track::drawCurves() {
  glColor3f(1,0,0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < curves.size(); i++) {
    for (int j = 0; j < 4; j++) {
      glVertex3f(curves[i]->getCP(j)[0], curves[i]->getCP(j)[1], -3.4);
    }
  }
  glEnd();
}

void Track::drawPoints() {
  glPointSize(10);
  glColor3f(0, 0, 1);

  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j < 4; j += 0.01) {
      glVertex3fv(curves[i]->getCPointer(j));
    }
  }
  glEnd();

}
