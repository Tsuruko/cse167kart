//
//  main.cpp
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 11/17/13
//
//  Modified: 12/7/13
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Matrix4.h"
#include "Track.h"
#include "BCurve.h"
#include "Texture.h"
#include "Camera.h"
#include "objreader.h"
#include "sphere.cpp"
#include "cube.cpp"
#include "car.h"

using namespace std;

GLuint trackTex;
GLuint rockTex;

Matrix4 trackSize;
Matrix4 mouse;  //for trackball rotating
//mouse variables
int clickx, clicky = 0;
bool lrb = true;
//toggle between default perspective and simulation perspective
bool mode = true;
//toggle control points on/off in edit mode
bool ctrlpts = true;
//toggle terrain on/off in car mode
bool terrain = false;
//toggle texture on/off
bool textureOn = false;
//toggle per vertex normals
bool vertNormal = true;

bool pause = false;

Camera *cam = new Camera(Vector3(0,0,0), Vector3(0,0,0), Vector3(0,0,1));

//track size and position adjustment constants
const float trackScale = 10.0;
const float transRatio = -2.5;

car * modelCar = new car(trackScale);
Track * track = new Track();

int nVerts;
float *vertices;
float *normals;
float *texcoords;
int nIndices;
int *indices;

int width  = 512;   // set window width in pixels here
int height = 512;   // set window height in pixels here

void idleCallback(void);
void reshapeCallback(int, int);
void displayCallback(void);

//just the DEFAULT track shape, no objects
//add params later to make more flexible, or different control pts, etc.
void makeTrack() {
  int multz = 2.0;
  int multy = 2.0;
  Vector3 * start = new Vector3(-2.5f, 2.5f*multy, 2.0f*multz);
  Vector3 * middle1 = new Vector3(-2.5f, -2.5f*multy, 0.0f);
  track->addCurve(new BCurve(start,
                             new Vector3(-2.5f,  2.5/3.0f*multy, 2.0f*multz),
                             new Vector3(-2.5f,  -2.5/3.0f*multy, 0.0f),
                             middle1));
  Vector3 * middle2 = new Vector3(2.5f, -2.5f*multy, -2.0f*multz);
  track->addCurve(new BCurve(middle1,
                             new Vector3(-2.5f, (-2.5f*multy)-4, 0.0f),
                             new Vector3(2.5f, (-2.5f*multy)-4, -2.0f*multz),
                             middle2));
  Vector3 * end = new Vector3(2.5f, 2.5f*multy, 0.0f);
  track->addCurve(new BCurve(middle2,
                             new Vector3(2.5f,  -2.5/3.0f*multy, -2.0f*multz),
                             new Vector3(2.5f, 2.5/3.0f*multy, 0.0f),
                             end));
  track->addCurve(new BCurve(end,
                             new Vector3(2.5f, (2.5f*multy)+4, 0.0f),
                             new Vector3(-2.5f, (2.5f*multy)+4, 2.0f*multz),
                             start));
  Vector3 * obj = new Vector3(-2.5f,  2.5/3.0f*multy, 2.0f*multz);
  track->addGeode(new sphere(0.1, *middle1));
  track->addGeode(new cube(0.2, *start));
  track->addGeode(new sphere(0.1, *end));
  track->addGeode(new cube(0.2, *middle2));
}

void idleCallback(void)
{
  if (!pause) {
    if (!mode) {
      cam->setEye(track->getPoint(cam->eye_t, 0.005, cam->eyeCurve));
      cam->setCenter(track->getPoint(cam->center_t, 0.005, cam->centerCurve));
      modelCar->moveForward(track->getPoint(modelCar->t, 0.005, modelCar->curve));
    }
    displayCallback();  // call display routine to re-draw
  }
}

inline float sgn(float a)
{
  if (a > 0.0F) return (1.0F);
  if (a < 0.0F) return (-1.0F);
  return (0.0F);
}


void ModifyProjectionMatrix(Vector4 * clip)
{
  float       matrix[16];
  Vector4    q;
  Vector4 clipPlane = *clip;
  
  // Grab the current projection matrix from OpenGL
  glGetFloatv(GL_PROJECTION_MATRIX, matrix);
  
  // Calculate the clip-space corner point opposite the clipping plane
  // as (sgn(clipPlane.x), sgn(clipPlane.y), 1, 1) and
  // transform it into camera space by multiplying it
  // by the inverse of the projection matrix
  
  q[0] = (sgn(clipPlane[0]) + matrix[8]) / matrix[0];
  q[1] = (sgn(clipPlane[1]) + matrix[9]) / matrix[5];
  q[2] = -1.0F;
  q[3] = (1.0F + matrix[10]) / matrix[14];
  
  // Calculate the scaled plane vector
	Vector4 c = clipPlane.scale(2.0F / (clipPlane.dot(q)));
  
  // Replace the third row of the projection matrix
	matrix[2] = c[0];
  matrix[6] = c[1];
  matrix[10] = c[2] + 1.0F;
  matrix[14] = c[3];
  
  // Load it back into OpenGL
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(matrix);
}


void reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  if (mode) glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);
}

void printTest(Vector4 t, const char* n) {
  std::cout << n << t[0] << ", " << t[1] << ", " << t[2] << ", " <<t[3] << std::endl;
}

void printWindow(string s) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, width, 0.0, height);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  glDisable(GL_LIGHTING);
  glColor3f(1.0, 0.0, 0.0);
  glRasterPos2i(20, 20);
  void * font = GLUT_BITMAP_HELVETICA_18;
  for (string::iterator i = s.begin(); i != s.end(); ++i)
  {
    char c = *i;
    glutBitmapCharacter(font, c);
  }
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

void checkCollision() {
  Vector4 carCenter = modelCar->getBoundingSphere();
  
  geode * currObj;
  float objRadius;
  Vector4 objCenter;
  for (int i = 0; i < track->getNumObj(); i++) {
    currObj = track->getObj(i);
    objCenter = currObj->getBoundingSphere();
    
    // printTest(carCenter, "car ");
    
    //check x and y direction
    if (carCenter[0]+carCenter[3] > objCenter[0]-objCenter[3] &&
        carCenter[0]-carCenter[3] < objCenter[0]+objCenter[3]) {
      if (carCenter[1]+carCenter[3] > objCenter[1]-objCenter[3] &&
          carCenter[1]-carCenter[3] < objCenter[1]+objCenter[3]) {
        printWindow("CRASH");
        pause = true;
      }
    }
  }
}

void displayCallback(void)
{
  if(!mode) ModifyProjectionMatrix(new Vector4(0,-1,-2,-1));
  //clear color and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (mode) {
    glDisable(GL_LIGHTING);
    glLoadMatrixf(mouse.getPointer());
    glClearColor(0.0, 0.0, 0.0, 0.0);           // set clear color to black
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1, 0.0, 1.0, 0.0);
    if (ctrlpts) track->drawPoints();
    track->drawCurves();
    track->drawObjects();
  } else {
    glLoadMatrixf(trackSize.getPointer());
    glEnable(GL_LIGHTING);
    glClearColor(0.0, 0.5, 1.0, 0.0);           // set clear color to blue
    gluLookAt(cam->getEye()[0], cam->getEye()[1], cam->getEye()[2],
              cam->getCenter()[0], cam->getCenter()[1], cam->getCenter()[2],
              cam->getUp()[0], cam->getUp()[1], cam->getUp()[2]);
    
    glBindTexture(GL_TEXTURE_2D, trackTex);
    if (textureOn) glEnable(GL_TEXTURE_2D);
    track->drawTrack();
    if (terrain){
      glBindTexture(GL_TEXTURE_2D, rockTex);
      track->drawTerrain();
    }
    if (textureOn) glDisable(GL_TEXTURE_2D);
    
    track->drawObjects();
    modelCar->draw();
    
    checkCollision();
  }
  
  glFlush();
  glutSwapBuffers();
}


void processKeys (unsigned char key, int x, int y) {
  if (key == 'r') {
    cam->reset();
    modelCar->reset();
    cam->setEye(track->getPoint(cam->eye_t, 0.01, cam->eyeCurve));
    cam->setCenter(track->getPoint(cam->center_t, 0.01, cam->centerCurve));
    modelCar->moveForward(track->getPoint(modelCar->t, 0.01, modelCar->curve));
    pause = false;
  }
  if (key == 'd') {
    if (mode) {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0);
      mode = false;
    } else {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0);
      glTranslatef(0, 0, -20);
      mode = true;
    }
  }
  if (key == 'c') {
    if (ctrlpts) ctrlpts = false;
    else ctrlpts = true;
  }
  if (key == 't') {
    if (terrain) terrain = false;
    else terrain = true;
  }
  if (key == 'x') {
    textureOn = !textureOn;
  }
  if (key=='n'){
    if(vertNormal) vertNormal = false;
    else vertNormal = true;
    track->setVertN(vertNormal);
  }
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_UP:
      cam->setEye(track->getPoint(cam->eye_t, 0.01, cam->eyeCurve));
      cam->setCenter(track->getPoint(cam->center_t, 0.01, cam->centerCurve));
      modelCar->moveForward(track->getPoint(modelCar->t, 0.01, modelCar->curve));
      break;
    case GLUT_KEY_LEFT:
      modelCar->moveSide(-0.4);
      break;
    case GLUT_KEY_RIGHT:
      modelCar->moveSide(0.4);
      break;
    default:
      break;
  }
}

void mouseButton(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    lrb = true;
  } else if (button == GLUT_RIGHT_BUTTON) {
    lrb = false;
  }
  clickx = x;
  clicky = y;
  std::cout << x <<endl;
}

void mouseMotion(int x, int y) {
  if (lrb) mouse = mouse.trackballRotation(512,512,x,y,clickx,clicky);
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(width, height);      // set initial window size
  glutCreateWindow("OpenGL Kart for CSE167");    	      // open window and set window title
  
  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  float ambLight0[4] = {0.4f, 0.4f, 0.4f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambLight0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);
  glutIdleFunc(idleCallback);
  
  //process mouse press and motion
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMotion);
  
  //process keystrokes
  glutKeyboardFunc(processKeys);
  glutSpecialFunc(processSpecialKeys);
  
  //initialize matrices
  mouse.identity();
  trackSize.identity();
  trackSize = Matrix4::scale(trackScale, trackScale, trackScale);
  makeTrack();
  trackTex = loadTexture("road3.ppm");
  rockTex = loadTexture("rock3.ppm");
  
  ObjReader::readObj("Porsche_911_GT2.obj", modelCar->nVerts, &modelCar->vertices,
                     &modelCar->normals, &modelCar->texcoords,
                     modelCar->nIndices, &modelCar->indices);
  modelCar->findMinMax(); 
  
  /* To Calculate Max Texture Size
   GLint texSize;
   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texSize);
   cout<<texSize<<endl;*/
  
  glutMainLoop();
  return 0;
}
