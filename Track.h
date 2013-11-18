//
//  Track.h
//  cse167kart
//
//  Created by Nick Troast on 11/17/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#ifndef __cse167kart__Track__
#define __cse167kart__Track__
#include <vector>
#include "BCurve.h"

class Track
{
private:
  std::vector<BCurve*> curves;
public:
  Track();
  void addCurve(BCurve*);
  void drawCurves();
  void drawPoints();
};

#endif /* defined(__cse167kart__Track__) */
