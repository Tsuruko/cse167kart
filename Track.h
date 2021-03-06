//
//  Track.h
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 11/17/13
//
//  Modified: 12/7/13
//

#ifndef __cse167kart__Track__
#define __cse167kart__Track__

#include <vector>
#include "BCurve.h"
#include "geode.h"

class Track {

private:

  std::vector<BCurve*> curves;
  std::vector<geode*> roadObjects;
  GLfloat stacks;
  GLfloat width;
  GLfloat eye_t; // Where we are on the curve
  GLfloat center_t;
  int eyeCurve; // The curve we are currently on
  int centerCurve;
  int laneCount;
  
  int maxInnerLevels;
  int maxOuterLevels;

  bool vertNormals;
  std::vector<std::vector<Vector3>* > innerLevels;
  std::vector<std::vector<Vector3>* > outerLevels;
  std::vector<std::vector<Vector3>* > innerLevelsN;
  std::vector<std::vector<Vector3>* > outerLevelsN;

  std::vector<float> upIRand;
  std::vector<float> outIRand;
  std::vector<float> upORand;
  std::vector<float> outORand;
  std::vector<float> upIBase;
  std::vector<float> outIBase;
  std::vector<float> upOBase;
  std::vector<float> outOBase;

  std::vector<Vector3> l0;
  std::vector<Vector3> r0;
  Vector3 genInner(Vector3 v1, Vector3 V2);
  Vector3 calcNormal(Vector3 v1, Vector3 v2, Vector3 v3,Vector3 v4, Vector3 v5);

public:
  Track();
  void addCurve(BCurve*);
  void addGeode(geode*);
  int getNumObj();
  geode * getObj(int);
  BCurve * getCurve(int);
  void drawCurves();
  void drawPoints();
  void drawTrack();
  void drawObjects();
  void drawRoadLines();
  void drawTerrain();
  void drawTerrainHelper(std::vector<Vector3> v1, std::vector<Vector3> v2, int level, std::vector<Vector3> n1, std::vector<Vector3> n2);
  Vector3 getPoint(GLfloat &t, GLfloat step, int &curve);
  void setVertN(bool flag);
  std::vector<geode*>* getRoadObjs();
};

#endif /* defined(__cse167kart__Track__) */
