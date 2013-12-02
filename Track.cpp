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
  eye_t = 0;
  center_t = 0.15;
  eyeCurve = 0;
  centerCurve = 0;
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
  glBegin(GL_POINTS);
  for (int i = 0; i < curves.size(); i++) {
    glColor3f(0,0,1);
    glVertex3fv(curves[i]->getCPointer(0));
    glColor3f(0,1,0);
    for (GLfloat j = 1; j < 3; j++) {
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
    if(texture) {
      glDisable(GL_TEXTURE_2D); 
    }
  }
  glEnd();
}

Vector3 Track::getNext(GLfloat step, int test)
{
  if (test == 0) {
  //check if the tstep needs to be reset
    if (eye_t + step > 1) {
    //loop back eyeCurve to first curve on the track
      if (eyeCurve == curves.size() - 1) eyeCurve = 0;
      else eyeCurve++;
      eye_t = step - (1 - eye_t);
    }
    else eye_t = eye_t + step;
    return curves[eyeCurve]->getPoint(eye_t);
  }
  else {
    if (center_t + step > 1) {
      if (centerCurve == curves.size() - 1) centerCurve = 0;
      else centerCurve++;
      center_t = step - (1 - center_t);
    }
    else center_t = center_t + step;
    return curves[centerCurve]->getPoint(center_t);
  }
}
