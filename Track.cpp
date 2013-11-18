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
  stacks = 0.05;
}

void Track::addCurve(BCurve * c) {
  curves.push_back(c);
}

void Track::drawCurves() {
  glColor3f(1,0,0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j <= 1; j += stacks) {
      glVertex3f(curves[i]->getPoint(j)[0], curves[i]->getPoint(j)[1], 
			curves[i]->getPoint(j)[2]);
    }
  }
  glEnd();
/*
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j <= 1; j += stacks) {
      glVertex3f(1.3*curves[i]->getPoint(j)[0], 1.3*curves[i]->getPoint(j)[1],
                        1.3*curves[i]->getPoint(j)[2]);
    }
  }
  glEnd();
*/
}


void Track::drawPoints() {
  glPointSize(10);
  glColor3f(0, 0, 1);
  glBegin(GL_POINTS);
  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j < 4; j++) {
      glVertex3fv(curves[i]->getCPointer(j));
    }
  }
  glEnd();
}

void Track::drawTrack() {
  //glBegin(??)
  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j <=1; j+= stacks) {
   //   glVertex3f();
   //   glNormal3f();
    }
  }
  //glEnd();
}
