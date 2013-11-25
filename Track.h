//
//  Track.h
//  cse167kart
//
//  Nick Troast, Monica Liu, Andrew Lin
//

#ifndef __cse167kart__Track__
#define __cse167kart__Track__
#include <vector>
#include "BCurve.h"

class Track
{
private:
  std::vector<BCurve*> curves;
  GLfloat stacks;
  GLfloat width;
  GLfloat t; // Where we are on the curve
  BCurve* currentCurve; // The curve we are currently on
  
public:
  bool texture;
  Track();
  void addCurve(BCurve*);
  void drawCurves();
  void drawPoints();
  void drawTrack();
  Vector3 getNext(GLfloat step);
};

#endif /* defined(__cse167kart__Track__) */
