//
//  Track.cpp
//  cse167kart
//
//  Nick Troast, Monica Liu, Andrew Lin
//

#include "Track.h"

Track::Track()
{
  curves.clear();
  stacks = 0.05;
  width = 0.5;
}

void Track::addCurve(BCurve * c) {
  curves.push_back(c);
}

void Track::drawCurves() {
  glColor3f(1,0,0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j <= 1+stacks; j += stacks) {
      glVertex3f(curves[i]->getPoint(j)[0], curves[i]->getPoint(j)[1], 
			curves[i]->getPoint(j)[2]);
    }
  }
  glEnd();
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
  glColor3f(1,1,1);
  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j <= 1+stacks; j += stacks) {
      Vector3 temp4((curves[i]->getTangent(j)));
        temp4.normalize();
      temp4 = temp4.scale(width);
	  if(texture) glTexCoord2f(0, (i)/(curves.size()));
      glNormal3f(0, 0, -1);
	glVertex3f(-temp4[1]+(curves[i]->getPoint(j))[0], 
		   temp4[0]+(curves[i]->getPoint(j))[1], 
		   curves[i]->getPoint(j)[2]);
	  if(texture) glTexCoord2f(1, (i)/(curves.size()));
      glNormal3f(0, 0, -1);
	glVertex3f(temp4[1]+(curves[i]->getPoint(j))[0], 
		   -temp4[0]+(curves[i]->getPoint(j))[1],
		   curves[i]->getPoint(j)[2]);
    }
  }
  glEnd();
}
