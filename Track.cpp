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
}

void Track::addCurve(BCurve c) {
  curves.push_back(c);
}
