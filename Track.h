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
  
public:
  bool texture;
  Track();
  void addCurve(BCurve*);
  void drawCurves();
  void drawPoints();
  void drawTrack();
};

#endif /* defined(__cse167kart__Track__) */
