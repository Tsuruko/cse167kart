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
  
  int maxInnerLevels;
  int maxOuterLevels;
  std::vector<std::vector<Vector3>* > innerLevels;
  std::vector<std::vector<Vector3>* > outerLevels;
  std::vector<float> upRand;
  std::vector<float> outRand;
  std::vector<Vector3> l0;
  std::vector<Vector3> r0;
  /*std::vector<Vector3> l1;
  std::vector<Vector3> l2;
  std::vector<Vector3> l3;
  std::vector<Vector3> l4;
  std::vector<Vector3> l5;
  std::vector<Vector3> l6;
  std::vector<Vector3> l7;
  std::vector<Vector3> l8;*/
  Vector3 genInner(Vector3 v1, Vector3 V2);
  Vector3 calcNormal(Vector3 v1);

public:
  Track();
  void addCurve(BCurve*);
  int getSize();
  BCurve * getCurve(int);
  void drawCurves();
  void drawPoints();
  void drawTrack();
  void drawRoadLines();
  void drawTerrain();
  void drawTerrainHelper(std::vector<Vector3> v1, std::vector<Vector3> v2, int level);
  Vector3 getPoint(GLfloat &t, GLfloat step, int &curve);
};

#endif /* defined(__cse167kart__Track__) */
