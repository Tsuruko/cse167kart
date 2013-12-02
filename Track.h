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
  GLfloat eye_t; // Where we are on the curve
  GLfloat center_t;
  int eyeCurve; // The curve we are currently on
  int centerCurve;
  int laneCount;
  
  std::vector<Vector3> verticesInner;
  std::vector<Vector3> verticesOuter;
  Vector3 genInner(Vector3 v1, Vector3 V2);

public:
  bool texture;
  Track();
  void addCurve(BCurve*);
  int getSize();
  BCurve * getCurve(int);
  void drawCurves();
  void drawPoints();
  void drawTrack();
  void drawRoadLines();
  void drawTerrain();
  Vector3 getNext(GLfloat step, int test);
};

#endif /* defined(__cse167kart__Track__) */
