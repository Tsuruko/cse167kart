//
//  FireCone.cpp
//  FireCone
//
//  Created by Nick Troast on 12/2/13.
//  Copyright (c) 2013 Nick Troast. All rights reserved.
//

#include "FireCone.h"
GLfloat g,b;

FireCone::FireCone() {
  scale = Matrix4().scale(0.1, 0.1, 0.1);
  for (int i = 0; i < 1000; i++) {
    particles.push_back(Particle());
  }
}

void FireCone::draw()
{
  glDisable(GL_LIGHTING);
  glPointSize(3);
  glBegin(GL_POINTS);
  for (std::vector<Particle>::iterator it = particles.begin() ; it != particles.end(); ++it)
  {
    it->v[0] = (it->v[2] / 5.0) * cos(it->theta * (PI / 180.0));
    it->v[1] = (it->v[2] / 5.0) * sin(it->theta * (PI / 180.0));
    
    if (it->v[2] > 0.5)
      g = 1.0 - ((it->v[2] - 0.5) * 2.0);
    else
      g = 1;
    
    b = 1.0 - it->v[2];
    glColor3f(1, g, b);
    
    glVertex3fv(it->v.getPointer());
    
    it->theta = (it->theta + 2) % 360;
    
    if (it->v[2] >= (1 + (rand() % 1000)/1000.0))
      it->v[2] = 0;
    else
      it->v[2] = it->v[2] + 0.01;
  }
  glEnd();
  glEnable(GL_LIGHTING);
}