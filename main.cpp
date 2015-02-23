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

#define WINDOWTITLE "OpenGL Kart for CSE167"
using namespace std;

string APP_PATH = "";
string appName = "carGame";

GLuint trackTex;
GLuint rockTex;

Matrix4 trackSize;
Matrix4 mouse;  //for trackball rotating
//mouse variables
int clickx, clicky = 0;
bool lrb = true;
//toggle between default perspective and simulation perspective
bool mode = false;
//toggle control points on/off in edit mode
bool ctrlpts = true;
//toggle terrain on/off in car mode
bool terrain = true;
//toggle texture on/off
bool textureOn = true;
//toggle per vertex normals
bool vertNormal = true;

GLboolean leftPressed = false;
GLboolean rightPressed = false;

bool pauseGame = true;
bool startScreen = true;

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

int frameCounter;
int width  = 512;   // set window width in pixels here
int height = 512;   // set window height in pixels here
int WindowHandle;

int widthS = 512;
int heightS = 512;
int widthHD = 910;
int heightHD = 512;

int frustWidth = 8;
 int geodeCurve[5] = {1,2,2,3,3};
 Vector3 geodeCenter[5];
 GLfloat geode_t[5] = {0,0,0.5,0,0.5};

unsigned int timeStart, timeEnd;

int speed = 16;

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

  geodeCenter[0] = track->getPoint(geode_t[0], 0.0, geodeCurve[0]);
  geodeCenter[1] = track->getPoint(geode_t[1], 0.0, geodeCurve[1]);
  geodeCenter[1][0] -= 0.2;
  geodeCenter[2] = track->getPoint(geode_t[2], 0.0, geodeCurve[2]);
  geodeCenter[2][0] += 0.2;
  geodeCenter[3] = track->getPoint(geode_t[3], 0.0, geodeCurve[3]);
  geodeCenter[4] = track->getPoint(geode_t[4], 0.0, geodeCurve[4]);
  track->addGeode(new sphere(0.1, geodeCenter[0]));
  track->addGeode(new cube(0.2, geodeCenter[1]));
  track->addGeode(new sphere(0.1, geodeCenter[2]));
  track->addGeode(new cube(0.2, geodeCenter[3]));
  track->addGeode(new sphere(0.1, geodeCenter[4]));
  frameCounter = 500;
}

void idleCallback(void)
{
  timeEnd = glutGet(GLUT_ELAPSED_TIME);
  if(timeEnd - timeStart >= speed){
    timeStart = glutGet(GLUT_ELAPSED_TIME);
    frameCounter++;
    if(frameCounter%100&&frameCounter<500){
      track->getRoadObjs()->at(4)->trans[1]+=.00045;
      track->getRoadObjs()->at(0)->trans[0]+=.00045;
      track->getRoadObjs()->at(1)->trans[0]-=.00045;
      track->getRoadObjs()->at(2)->trans[0]+=.00045;
      track->getRoadObjs()->at(3)->trans[0]-=.00045;

    }
    else if(frameCounter%100&&frameCounter>=500){
    track->getRoadObjs()->at(4)->trans[1]-=.00045; 
    track->getRoadObjs()->at(0)->trans[0]-=.00045;
    track->getRoadObjs()->at(1)->trans[0]+=.00045; 
    track->getRoadObjs()->at(2)->trans[0]-=.00045; 
    track->getRoadObjs()->at(3)->trans[0]+=.00045; 

    }
    if(frameCounter>1000){
      frameCounter = 0;
    }
    if (!pauseGame) {
      if (!mode) {
        cam->setEye(track->getPoint(cam->eye_t, 0.006, cam->eyeCurve));
        cam->setCenter(track->getPoint(cam->center_t, 0.006, cam->centerCurve));
        modelCar->moveForward(track->getPoint(modelCar->t, 0.006, modelCar->curve));
        if (leftPressed)
          modelCar->moveSide(-0.07);
        if (rightPressed)
          modelCar->moveSide(0.07);
      }
      displayCallback();  // call display routine to re-draw
    }
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
  glFrustum(-10.0, 10.0, -frustWidth, frustWidth, 10, 1000.0); // set perspective projection viewing frustum
  if (mode) glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);
}

void printTest(Vector4 t, const char* n) {
  std::cout << n << t[0] << ", " << t[1] << ", " << t[2] << ", " <<t[3] << std::endl;
}

void drawText(int x, int y, string text, float r, float g, float b, void * font) {
    glColor3f(r, g, b);//needs to be called before RasterPos
    glRasterPos2i(x, y);
    
    for (std::string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        //this does nothing, color is fixed for Bitmaps when calling glRasterPos
        //glColor3f(1.0, 0.0, 1.0);
        glutBitmapCharacter(font, c);
    }
}

void printWindow() {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, width, 0.0, height);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
    
  float r = 1.0;
  float g = 1.0;
  float b = 1.0;
  int w_off = 20;
  int h_off = height*4/5;
  if (!startScreen) drawText(w_off, 20, "CRASH! Game Over", 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18);

  drawText(w_off, height-20, "Press ESC to exit", r, g, b, GLUT_BITMAP_HELVETICA_18);
  
  drawText(w_off, h_off, "Game Controls", r, g, b, GLUT_BITMAP_HELVETICA_18);
  drawText(w_off, h_off-20, "Press 'r' to restart game", r, g, b, GLUT_BITMAP_HELVETICA_12);
  drawText(w_off, h_off-40,
           "Use left and right arrow keys to move the car", r, g, b, GLUT_BITMAP_HELVETICA_12);
  drawText(w_off, h_off-55,
           "Use up and down arrow keys to change the car's speed", r, g, b, GLUT_BITMAP_HELVETICA_12);
  
  drawText(w_off, h_off-80, "Debugging Controls", r, g, b, GLUT_BITMAP_HELVETICA_18);
  drawText(w_off, h_off-100, "Press 's' and 'h' to toggle viewing size", r, g, b, GLUT_BITMAP_HELVETICA_12);
  drawText(w_off, h_off-115, "Press 't' to toggle viewing terrain", r, g, b, GLUT_BITMAP_HELVETICA_12);
  drawText(w_off, h_off-130, "Press 'x' to toggle viewing textures", r, g, b, GLUT_BITMAP_HELVETICA_12);
  drawText(w_off, h_off-145, "Press 'n' to toggle normals", r, g, b, GLUT_BITMAP_HELVETICA_12);
  drawText(w_off, h_off-160, "Press 'd' to switch to debug edit mode", r, g, b, GLUT_BITMAP_HELVETICA_12);
    
  drawText(w_off, h_off-190, "In edit mode", r, g, b, GLUT_BITMAP_HELVETICA_18);
  drawText(w_off, h_off-205, "Press 'c' to toggle viewing control points", r, g, b, GLUT_BITMAP_HELVETICA_12);
    
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

void checkCollision() {
  Vector4 carCenter = modelCar->getBoundingSphere();
  geode * currObj;
  Vector4 objCenter;
  for (int i = 0; i < track->getNumObj(); i++) {
    currObj = track->getObj(i);
    objCenter = currObj->getBoundingSphere();
    GLfloat dx = carCenter[0] - objCenter[0];
    GLfloat dy = carCenter[1] - objCenter[1];
    GLfloat dz = carCenter[2] - objCenter[2];
    
    GLfloat distance = sqrt(dx*dx + dy*dy + dz*dz);
    
    if (distance <= (carCenter[3] + objCenter[3])) {
      pauseGame = true;
      printWindow();
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
    track->getRoadObjs()->at(1)->trans=track->getPoint(geode_t[1], 0.0, geodeCurve[1]);
    track->getRoadObjs()->at(2)->trans=track->getPoint(geode_t[2], 0.0, geodeCurve[2]);
    track->getRoadObjs()->at(3)->trans=track->getPoint(geode_t[3], 0.0, geodeCurve[3]);
    track->getRoadObjs()->at(4)->trans=track->getPoint(geode_t[4], 0.0, geodeCurve[4]);
    track->getRoadObjs()->at(0)->trans=track->getPoint(geode_t[0], 0.0, geodeCurve[0]);
    frameCounter = 0;
    speed = 16;
    pauseGame = false;
    startScreen = false;
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
  if (key=='s'){
    glutReshapeWindow(widthS,heightS);
    frustWidth = 10;
  }
  if(key=='h'){
    glutReshapeWindow(widthHD,heightHD);
    frustWidth = 8;
  }
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_UP:
      speed--;
      if(speed<0) speed = 0;
      
      break;
     case GLUT_KEY_DOWN:
      speed++;
      break;
    case GLUT_KEY_LEFT:
      leftPressed = true;
      //modelCar->moveSide(-0.4);
      break;
    case GLUT_KEY_RIGHT:
      rightPressed = true;
      //modelCar->moveSide(0.4);
      break;
    default:
      break;
  }
}

void processSpecialUpKeys(int key, int x, int y) {
  switch(key) {
      case 0x1b:		// Escape
        glFinish();
        glutDestroyWindow(WindowHandle);
        exit(0);
        break;
    case GLUT_KEY_LEFT:
      leftPressed = false;
      break;
    case GLUT_KEY_RIGHT:
      rightPressed = false;
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
}

void mouseMotion(int x, int y) {
  if (lrb) mouse = mouse.trackballRotation(512,512,x,y,clickx,clicky);
}

int main(int argc, char *argv[])
{
  APP_PATH = argv[0];
    
  if (APP_PATH.find("Xcode") == std::string::npos) {
    string::size_type i = APP_PATH.find(appName);
        
    if (i != std::string::npos)
      APP_PATH.erase(i, appName.length());
      APP_PATH = APP_PATH + "/";
    } else {
      APP_PATH = "";
  }
    
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(widthHD, heightHD);      // set initial window size
  WindowHandle = glutCreateWindow(WINDOWTITLE);    	      // open window and set window title
  glutSetWindowTitle( WINDOWTITLE );
  glutSetWindow( WindowHandle );
  
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
  glutSpecialUpFunc(processSpecialUpKeys);
  
  //initialize matrices
  mouse.identity();
  trackSize.identity();
  trackSize = Matrix4::scale(trackScale, trackScale, trackScale);
  makeTrack();
  string fileString = APP_PATH + "road3.ppm";
  trackTex = loadTexture(fileString.c_str());
  fileString = APP_PATH + "rock3.ppm";
  rockTex = loadTexture(fileString.c_str());
  fileString = APP_PATH + "Porsche_911_GT2.obj";
  ObjReader::readObj(fileString.c_str(), modelCar->nVerts, &modelCar->vertices,
                     &modelCar->normals, &modelCar->texcoords,
                     modelCar->nIndices, &modelCar->indices);
  modelCar->findMinMax(); 
  timeStart = glutGet(GLUT_ELAPSED_TIME);
  /* To Calculate Max Texture Size
   GLint texSize;
   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texSize);
   cout<<texSize<<endl;*/
  
  glutMainLoop();
  return 0;
}
