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
  stacks = 0.01;
  width = 0.5;
  t = 0;
  currentCurve = 0;
  laneCount = 2;
}

void Track::addCurve(BCurve * c) {
  curves.push_back(c);
}

int Track::getSize() {
  return curves.size();
}

BCurve * Track::getCurve(int i) {
  if (i < 0) return NULL;
  if (i >= curves.size()) return NULL;
  return curves[i];
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
}

void Track::drawPoints() {
  glPointSize(10);
  //glColor3f(0, 0, 1);
  glBegin(GL_POINTS);
  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j < 4; j++) {
      if (j == 0) glColor3f(0,0,1);
      else glColor3f(0,1,0);
      glVertex3fv(curves[i]->getCPointer(j));
    }
  }
  glEnd();
}

void Track::drawTrack() {
  glColor3f(1,1,1);
  glBegin(GL_QUAD_STRIP);
  if(texture){
	  glEnable(GL_TEXTURE_2D); 
  }
  int texHeight = 0;
  for (int i = 0; i < curves.size(); i++) {
	  
    for (GLfloat j = 0; j <= 1; j += stacks) {
	  texHeight++;
	  if(texHeight>11) texHeight%=10;
      Vector3 temp4((curves[i]->getTangent(j)));
        temp4.normalize();
      temp4 = temp4.scale(width);
	  if(texture) glTexCoord2f(0, (texHeight/10.0));
      glNormal3f(0, 0, 1);
	glVertex3f(-temp4[1]+(curves[i]->getPoint(j))[0], 
		   temp4[0]+(curves[i]->getPoint(j))[1], 
		   curves[i]->getPoint(j)[2]);
	  if(texture) glTexCoord2f(laneCount, (texHeight/10.0));
      glNormal3f(0, 0, 1);
	glVertex3f(temp4[1]+(curves[i]->getPoint(j))[0], 
		   -temp4[0]+(curves[i]->getPoint(j))[1],
		   curves[i]->getPoint(j)[2]);
    }
	if(texture){
		glDisable(GL_TEXTURE_2D); 
	}
  }
  glEnd();
}

void Track::drawRoadLines() {

}

Vector3 Track::getNext(GLfloat step)
{

  if (t + step > 1) {
    if (currentCurve == curves.size() - 1) {
      currentCurve = 0;
    }
    else
    {
      currentCurve++;
    }
    t = step - (1 - t);
  }
  else
  {
    t = t + step;
  }
  return curves[currentCurve]->getPoint(t);
}
