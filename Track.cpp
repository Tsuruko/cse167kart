//
//  Track.cpp
//  cse167kart
//
//  Nick Troast, Monica Liu, Andrew Lin
//

#include "Track.h"
#include <stdlib.h>

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
  glEnable(GL_TEXTURE_2D); 
  int texHeight = 0;
  int vertCounter = 0;
  for (int i = 0; i < curves.size(); i++) { 
    
    
    for (GLfloat j = 0; j <= 1; j += stacks) {
//code for rendering track
      Vector3 temp4((curves[i]->getTangent(j)));
      temp4.normalize();
      temp4 = temp4.scale(width);
      texHeight++;
      if(texHeight>11) texHeight%=10;
 
     Vector3 v1(-temp4[1]+(curves[i]->getPoint(j))[0], 
                 temp4[0]+(curves[i]->getPoint(j))[1], 
        	 curves[i]->getPoint(j)[2]);

      Vector3 v2(temp4[1]+(curves[i]->getPoint(j))[0], 
                 -temp4[0]+(curves[i]->getPoint(j))[1],
                 curves[i]->getPoint(j)[2]);

      glTexCoord2f(0, (texHeight/10.0)); //Texture
      glNormal3f(0, 0, 1);
      glVertex3f(v1[0],v1[1],v1[2]);

      glTexCoord2f(laneCount, (texHeight/10.0)); //Texture
      glNormal3f(0, 0, 1);
      glVertex3f(v2[0],v2[1],v2[2]);

      //code for rendering terrain
      if(l0.size()<400){
      Vector3 v3(-temp4[1]+(curves[i]->getPoint(j))[0], 
            	 temp4[0]+(curves[i]->getPoint(j))[1], 
        	     curves[i]->getPoint(j)[2]);
      l0.push_back(v3);

 
      temp4 = temp4.scale(1.2);
     /* Vector3 v4(-temp4[1]+(curves[i]->getPoint(j))[0],  // ORIGINAL
            	 temp4[0]+(curves[i]->getPoint(j))[1], 
        	     curves[i]->getPoint(j)[2]);*/ 

      Vector3 v4(-temp4[1]+v3[0],//+rand()%3/4.0,  
            	 temp4[0]+v3[1],//+rand()%3/4.0, 
        	     v3[2]+rand()%3/2.0+1/2);
      l1.push_back(v4);

      temp4 = temp4.scale(1.1);
     /* Vector3 v5(-temp4[1]+(curves[i]->getPoint(j))[0], // ORIGINAL
            	 temp4[0]+(curves[i]->getPoint(j))[1], 
        	     curves[i]->getPoint(j)[2]);*/

      Vector3 v5(-temp4[1]+v4[0],//+rand()%3/4.0, 
            	 temp4[0]+v4[1],//+rand()%3/5.0, 
        	     v4[2]);//+rand()%3/2.0+2/2);
      l2.push_back(v5);

      temp4 = temp4.scale(1.1);
      /*
      Vector3 v6(-temp4[1]+(curves[i]->getPoint(j))[0], // ORIGINAL
            	 temp4[0]+(curves[i]->getPoint(j))[1], 
        	     curves[i]->getPoint(j)[2]);*/
      Vector3 v6(-temp4[1]+v5[0],//+rand()%3/4.0, 
            	 temp4[0]+v5[1],//+rand()%3/5.0, 
        	     v5[2]);//+rand()%3/2.0+3/2);
      l3.push_back(v6);

	  }
  //l1.push_back(genInner(l0[l0.size()-1],v1));
    }
        glDisable(GL_TEXTURE_2D); 
  }
  glEnd();
}

void Track::drawTerrain(){
  /*
  glColor3f(1,0,0);
  glNormal3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < l0.size(); i++) {
      glVertex3f(l0[i][0],l0[i][1],l0[i][2]);
  }
  glEnd();

  glColor3f(1,0,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < l1.size(); i++) {
      glVertex3f(l1[i][0],l1[i][1],l1[i][2]);
  }
  glEnd();

  glColor3f(1,0,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < l1.size(); i++) {
      glVertex3f(l2[i][0],l2[i][1],l2[i][2]);
  }
  glEnd();

  glColor3f(1,0,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < l1.size(); i++) {
      glVertex3f(l3[i][0],l3[i][1],l3[i][2]);
  }
  glEnd();*/


  glColor3f(1,1,1);
  //glNormal3f(0, 0, 1);
  glBegin(GL_QUAD_STRIP);
  glEnable(GL_TEXTURE_2D); 
  float lastS0 = 0;
  float lastT0 = 0;
  float lastS1 = 0;
  float lastT1 = 0;
  int texHeight=1;
  for (int i = 0; i < l0.size(); i++) {
      texHeight++;
      if(texHeight>11) texHeight%=10;



      glTexCoord2f(texHeight,0);
      lastS0 = l0[i][0];//-l0[i][0]/1;
      lastT0 = l0[i][2];//-l0[i][2]/1;
      glNormal3f(-l0[i][1], l0[i][0], 1);
      glVertex3f(l0[i][0],l0[i][1],l0[i][2]);

      glTexCoord2f(l1[i][0]-l0[i][0]+texHeight,l1[i][2]/20.0);
      glNormal3f(-l1[i][1], l1[i][0], 1);
      glVertex3f(l1[i][0],l1[i][1],l1[i][2]);
      lastS1 = l1[i][0];//-l1[i][0]/1;
      lastT1 = l1[i][2];//-l1[i][2]/1;
  }
  

  glNormal3f(-l0[0][1], l0[0][0], 1);
  glVertex3f(l0[0][0],l0[0][1],l0[0][2]);
  glNormal3f(-l1[0][1], l1[0][0], 1);
  glVertex3f(l1[0][0],l1[0][1],l1[0][2]);

  glEnd();

  glColor3f(1,1,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i < l0.size(); i++) {

      glNormal3f(-l2[i][1], l2[i][0], 1);
      glVertex3f(l2[i][0],l2[i][1],l2[i][2]);
      glNormal3f(-l1[i][1], l1[i][0], 1);
      glVertex3f(l1[i][0],l1[i][1],l1[i][2]);
  }
  glNormal3f(-l2[0][1], l2[0][0], 1);
  glVertex3f(l2[0][0],l2[0][1],l2[0][2]);
  glNormal3f(-l1[0][1], l1[0][0], 1);
  glVertex3f(l1[0][0],l1[0][1],l1[0][2]);
  
  glEnd();

  glColor3f(1,1,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i < l0.size(); i++) {

      glNormal3f(-l3[i][1], l3[i][0], 1);
      glVertex3f(l3[i][0],l3[i][1],l3[i][2]);

      glNormal3f(-l2[i][1], l2[i][0], 1);
      glVertex3f(l2[i][0],l2[i][1],l2[i][2]);
  }
  glNormal3f(-l3[0][1], l3[0][0], 1);
  glVertex3f(l3[0][0],l3[0][1],l3[0][2]);
  glNormal3f(-l2[0][1], l2[0][0], 1);
  glVertex3f(l2[0][0],l2[0][1],l2[0][2]);
  glDisable(GL_TEXTURE_2D); 
  glEnd();

  /*
 glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(l0[0][0],l0[0][1],l0[0][2]);
  glVertex3f(l1[0][0],l1[0][1],l1[0][2]);

  for (int i = 1; i < l1.size()/2; i++) {

      glVertex3f(l0[2*i-1][0],l0[2*i-1][1],l0[2*i-1][2]);
          glVertex3f(l1[i][0],l1[i][1],l1[i][2]);
          glVertex3f(l0[2*i][0],l0[2*i][1],l0[2*i][2]);

  }
  glEnd();
  l0.clear();
  l1.clear();*/
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


Vector3 genInner(Vector3 v1, Vector3 v2){
        Vector3 v3(0,0,0);
        return v3;

}

Vector3 calcNormal(Vector3 v1){
  Vector3 vec, norm;
  /**
  Vector4 test1, test2, test3, test4;

  Matrix4 r;




 
      vec = v1;
      norm = Vector3(-v1[1], v1[0], 0);




      norm.normalize();



      test1 = Vector4(v1[0], v1[1], v1[2], 1);
      test3 = Vector4(norm[0], norm[1], norm[2], 1);

      test1 = r * test1;

      test3 = r * test3;


      norm = Vector3(test3[0], test3[1], test3[2]);


      */ return vec;





}