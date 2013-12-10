//
//  Track.cpp
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 11/17/13
//
//  Modified: 12/7/13
//

#include "Track.h"
#include <stdlib.h>
#include <cmath>

Track::Track() {
  curves.clear();
  roadObjects.clear();
  stacks = 0.005;
  width = 0.5;
  eye_t = 0;
  center_t = 0.15;
  eyeCurve = 0;
  centerCurve = 0;
  laneCount = 2;
  maxInnerLevels = 9;
  maxOuterLevels = 9;
  vertNormals = true;
  //double arr[] = {.2,.3,.4,.4,.3,.4,.3,.2};
  //double arr2[] = {.5,.5,.25,.05,-.5,-.5,.3,.4};
  double arr[] = {.2,.3,.5,.5,.5,.5,.5,.5};
  double arr2[] = {.55,.35,0,0,0,0,0,0};
  innerLevels.push_back(&l0);
  upIBase.push_back(0);
  outIBase.push_back(0);
  innerLevelsN.push_back(new std::vector<Vector3>);

  for(int i=0;i<maxInnerLevels-1;i++){
    std::vector<Vector3>* temp =  new std::vector<Vector3>;
    innerLevels.push_back(temp);
    
    std::vector<Vector3>* temp2 =  new std::vector<Vector3>;
    innerLevelsN.push_back(temp2);

    upIBase.push_back(arr[i]);
    outIBase.push_back(arr2[i]);
  }
  
  upOBase.push_back(0);
  outOBase.push_back(0);
  outerLevels.push_back(&r0);
  outerLevelsN.push_back(new std::vector<Vector3>);

  for(int i=0;i<maxOuterLevels-1;i++){
    std::vector<Vector3>* temp =  new std::vector<Vector3>;
    outerLevels.push_back(temp);
    
    std::vector<Vector3>* temp2 =  new std::vector<Vector3>;
    outerLevelsN.push_back(temp2);

    upOBase.push_back(arr[i]);
    outOBase.push_back(arr2[i]);
  }
}

void Track::addCurve(BCurve * c) {
  curves.push_back(c);
}

void Track::addGeode(geode * g) {
  roadObjects.push_back(g);
}

int Track::getNumObj() {
  return roadObjects.size();
}

geode * Track::getObj(int i) {
  return roadObjects[i];
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
  int texHeight = 0;
  int vertCounter = 0;
  for (int i = 0; i < curves.size(); i++) {
    
    //code for rendering track
    for (GLfloat j = 0; j <= 1; j += stacks) {
      Vector3 temp4((curves[i]->getTangent(j)));
      temp4.normalize();
      temp4 = temp4.scale(width);
      
      if(texHeight>10) texHeight=1;
      
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
      
      if(texHeight==10){
        glTexCoord2f(0, (0/10.0)); //Texture
        glNormal3f(0, 0, 1);
        glVertex3f(v1[0],v1[1],v1[2]);
        
        glTexCoord2f(laneCount, (0/10.0)); //Texture
        glNormal3f(0, 0, 1);
        glVertex3f(v2[0],v2[1],v2[2]);
        
      }
      
      texHeight++;
      
      //code for generating terrain vertices- Version 1
      if(l0.size()<(4.0/(stacks*1.0))){ // Must be changed if levels differ

      Vector3 v3(-temp4[1]+(curves[i]->getPoint(j))[0], 
            	 temp4[0]+(curves[i]->getPoint(j))[1], 
        	     curves[i]->getPoint(j)[2]);
      l0.push_back(v3);
      Vector3 v4(temp4[1]+(curves[i]->getPoint(j))[0], 
               -temp4[0]+(curves[i]->getPoint(j))[1],
               curves[i]->getPoint(j)[2]);            
      r0.push_back(v4);



      int reset = 0;
      Vector3 original = temp4;

      upIRand.clear();
      upORand.clear();
      outIRand.clear();
      outORand.clear();


      for(int k=0;k<innerLevels.size();k++){

        //srand(k);
       if(k!=0){
        upIRand.push_back(std::pow(-1.0,(rand()%2))*(rand()%5)/40.0);
        upORand.push_back(std::pow(-1.0,(rand()%2))*(rand()%5)/40.0);
        outIRand.push_back(std::pow(-1.0,(rand()%2))*(rand()%5)/10.0);
        outORand.push_back(std::pow(-1.0,(rand()%2))*(rand()%5)/10.0);
       }
       else{
        upIRand.push_back(std::pow(-1.0,(rand()%2))*(rand()%5)/40.0);
        upORand.push_back(std::pow(-1.0,(rand()%2))*(rand()%5)/40.0);
        outIRand.push_back((rand()%5)/40.0);
        outORand.push_back((rand()%5)/40.0);
       }
      }

      for(int k=1;k<innerLevels.size();k++){
        temp4 = original;
        temp4 = temp4.scale(outIBase[k]+outIRand[k]);//1+std::pow(-1.0,(rand()%2))*(rand()%5)/10.0);
        v3[0] = -temp4[1]+v3[0];
        v3[1] =	 temp4[0]+v3[1],
        v3[2] =  v3[2]+upIBase[k]+upIRand[k];
        innerLevels[k]->push_back(v3);
      }

      temp4 = original;

      for(int k=1;k<outerLevels.size();k++){
        temp4 = original;
        temp4 = temp4.scale(outOBase[k]+outIRand[k]);//1+std::pow(-1.0,(rand()%2))*(rand()%5)/10.0);
        v4[0] = temp4[1]+v4[0];
        v4[1] =	-temp4[0]+v4[1],
        v4[2] =  v4[2]+upOBase[k]+upORand[k];
        outerLevels[k]->push_back(v4);
      }
    }
  }
  }
  glEnd();
}


void Track::drawObjects() {
  for (int i = 0; i < roadObjects.size(); i++) {
    roadObjects[i]->draw();
  }
}

void Track::drawTerrainHelper(std::vector<Vector3> v1, std::vector<Vector3> v2, int level, std::vector<Vector3> n1, std::vector<Vector3> n2){
  glColor3f(1,1,1);
  glBegin(GL_QUAD_STRIP);
  Vector3 n;
  int texHeight=1;
  int repeatX = 5; //5
  int repeatY = 4; //4
  if(level >6) {
    repeatX = 10;
    repeatY = 8;
  }
  for (int i = 0; i < v1.size(); i++) {
    //calculate normal
    n = Vector3::cross(v1[i], v2[i]);
    
    if(texHeight>repeatX) texHeight=1;
    
    glTexCoord2f(texHeight/(repeatX*1.0),level/(maxInnerLevels*1.0/repeatY));
    if(vertNormals) glNormal3f(n1[i][0],n1[i][1],n1[i][2]);
    else glNormal3fv(n.getPointer());
    glVertex3f(v1[i][0],v1[i][1],v1[i][2]);
    
    glTexCoord2f(texHeight/(repeatX*1.0),(level+1)/(maxInnerLevels*1.0/repeatY));
    if(vertNormals) glNormal3f(n2[i][0],n2[i][1],n2[i][2]);
    else glNormal3fv(n.getPointer());
    glVertex3f(v2[i][0],v2[i][1],v2[i][2]);
    
    // What is this part for? //The texture wraparound bug 
    if (texHeight==repeatX&&((i+1)!=v1.size())){
      glTexCoord2f(0/repeatX*1.0,level/(maxInnerLevels*1.0/repeatY));
      if(vertNormals) glNormal3f(n1[i][0],n1[i][1],n1[i][2]);
      else glNormal3fv(n.getPointer());
      glVertex3f(v1[i][0],v1[i][1],v1[i][2]);

      glTexCoord2f(0/(repeatX*1.0),(level+1)/(maxInnerLevels*1.0/repeatY));
      if(vertNormals) glNormal3f(n2[i][0],n2[i][1],n2[i][2]);
      else glNormal3fv(n.getPointer());
      glVertex3f(v2[i][0],v2[i][1],v2[i][2]);
    }
    
    
    texHeight++;
  }
  glEnd();
  
  int i;
  glBegin(GL_QUAD_STRIP);

  i = v1.size() - 1;
  n = Vector3::cross(v1[i], v2[i]);
  glTexCoord2f(0/repeatX*1.0,level/(maxInnerLevels*1.0/repeatY));
  if(vertNormals) glNormal3f(n1[i][0],n1[i][1],n2[i][2]);
  else glNormal3fv(n.getPointer());
  glVertex3f(v1[i][0],v1[i][1],v1[i][2]);

  i = v1.size() - 1;
  n = Vector3::cross(v1[i], v2[i]);
  glTexCoord2f(0/repeatX*1.0,(level+1)/(maxInnerLevels*1.0/repeatY));
  if(vertNormals) glNormal3f(n2[i][0],n2[i][1],n2[i][2]);
  else glNormal3fv(n.getPointer());
  glVertex3f(v2[i][0],v2[i][1],v2[i][2]);
  i = 0;
  n = Vector3::cross(v1[i], v2[i]);
  glTexCoord2f(1/(repeatX*1.0),level/(maxInnerLevels*1.0/repeatY));
  if(vertNormals) glNormal3f(n1[i][0],n1[i][1],n1[i][2]);
  else glNormal3fv(n.getPointer());
  glVertex3f(v1[i][0],v1[i][1],v1[i][2]);
  
  i = 0;
  n = Vector3::cross(v1[i], v2[i]);
  glTexCoord2f(1/(repeatX*1.0),(level+1)/(maxInnerLevels*1.0/repeatY));
  if(vertNormals) glNormal3f(n2[i][0],n2[i][1],n2[i][2]);
  else glNormal3fv(n.getPointer());
  glVertex3f(v2[i][0],v2[i][1],v2[i][2]);
  glEnd();
}


void Track::drawTerrain(){
  
  if((innerLevelsN[0]->size())<801){//(4.0/(stacks*1.0))){
    for(int i=0;i<maxInnerLevels;i++){
      for(int j=0;j<innerLevels[i]->size();j++){
      
        int j1;
        int j2;
      
        if((j)==(innerLevels[i]->size()-1)){ j1 = 0;}
        else{j1 = j+1;};

        if((j==0)){ j2 = (innerLevels[i]->size()-1);}
        else{j2 = j-1;}
        
      
        if(i==0){
            innerLevelsN[i]->push_back(calcNormal(innerLevels[i]->at(j),innerLevels[i]->at((j+1)%(innerLevels[i]->size()-1)),innerLevels[i]->at(j), innerLevels[i]->at(j2), innerLevels[i]->at(j)));
        }
        else if(i==(maxInnerLevels-1)){
            innerLevelsN[i]->push_back(calcNormal(innerLevels[i]->at(j),innerLevels[i]->at((j+1)%(innerLevels[i]->size()-1)),innerLevels[i]->at(j), innerLevels[i]->at(j2), innerLevels[i-1]->at(j)));
        }
        else{
            innerLevelsN[i]->push_back(calcNormal(innerLevels[i]->at(j),innerLevels[i]->at((j+1)%(innerLevels[i]->size()-1)),innerLevels[i]->at(j), innerLevels[i]->at(j2), innerLevels[i-1]->at(j)));
        }
      }
    }
  }
  
   if(outerLevelsN[0]->size()<(4.0/stacks)){
    for(int i=0;i<maxOuterLevels;i++){
      for(int j=0;j<outerLevels[i]->size();j++){
      
        int j1;
        int j2;
      
        if((j)==(outerLevels[i]->size()-1)){ j1 = 0;}
        else{j1 = j+1;};

        if((j==0)){ j2 = (outerLevels[i]->size()-1);}
        else{j2 = j-1;}

      
        if(i==0){
          outerLevelsN[i]->push_back(calcNormal(outerLevels[i]->at(j),outerLevels[i]->at((j+1)%(outerLevels[i]->size()-1)),outerLevels[i]->at(j), outerLevels[i]->at(j2), outerLevels[i]->at(j)));
        }
        else if(i==maxInnerLevels-1){
          outerLevelsN[i]->push_back(calcNormal(outerLevels[i]->at(j),outerLevels[i]->at((j+1)%(outerLevels[i]->size()-1)),outerLevels[i]->at(j), outerLevels[i]->at(j2), outerLevels[i-1]->at(j)));
        }
        else{
          outerLevelsN[i]->push_back(calcNormal(outerLevels[i]->at(j),outerLevels[i]->at((j+1)%(outerLevels[i]->size()-1)),outerLevels[i]->at(j), outerLevels[i]->at(j2), outerLevels[i-1]->at(j)));
        }
      }
    }
  }
  
  for(int i=0;i<maxInnerLevels-1;i++){
    drawTerrainHelper(*innerLevels[i],*innerLevels[i+1],i, *innerLevelsN[i],*innerLevelsN[i+1]);
  }
  
  for(int i=0;i<maxOuterLevels-1;i++){
    drawTerrainHelper(*outerLevels[i],*outerLevels[i+1],i,*outerLevelsN[i],*outerLevelsN[i+1]);
  }
}

Vector3 Track::getPoint(GLfloat &t, GLfloat step, int &curve)
{
  //check if the tstep needs to be reset
  if (t + step > 1) {
    //loop back eyeCurve to first curve on the track
    if (curve == curves.size() - 1) curve = 0;
    else curve++;
    t = step - (1 - t);
  }
  else t = t + step;
  return curves[curve]->getPoint(t);
}


Vector3 genInner(Vector3 v1, Vector3 v2){
  Vector3 v3(0,0,0);
  return v3;
  
}


Vector3 Track::calcNormal(Vector3 v0, Vector3 v1,Vector3 v2, Vector3 v3, Vector3 v4){
  Vector3 res(0,0,0);
  Vector3 norm;
  Vector3 vec[5] = {v0,v1,v2,v3,v4};
  Vector3 temp;

  for(int i = 0;i<4;i++){
    int j = i+1;
    if(j==5) j=1;
  temp = Vector3::cross(vec[i], vec[j]);
  temp.normalize();
  res = res+temp;
  }
  /*
  Vector3::cross(v1-v0, v2-v0);
  Vector3::cross(v2-v0, v3-v0);
  Vector3::cross(v3-v0, v4-v0);
  Vector3::cross(v4-v0, v1-v0);
  */

  return res;
  
  
}

void Track::setVertN(bool flag){
  vertNormals = flag;
}