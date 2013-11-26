//
//  main.cpp
//  cse167kart
//
//  Nick Troast, Monica Liu, Andrew Lin
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

using namespace std;

Matrix4 model;
Matrix4 trackSize;
Matrix4 mouse;  //for trackball rotating
//trackball capability
int clickx, clicky = 0;
bool lrb = true;
//toggle between default perspective and simulation perspective
bool mode = true;
Camera cam = Camera(Vector3(0,0,0), Vector3(0,0,0), Vector3(0,0,1));

//toggle texture
bool texture = false;

//track size and position adjustment constants
const float trackScale = 10.0;
const float transRatio = -2.5;

Track * track = new Track();

int width  = 512;   // set window width in pixels here
int height = 512;   // set window height in pixels here

void idleCallback(void);
void reshapeCallback(int, int);
void displayCallback(void);

//just the DEFAULT track shape, no objects
//add params later to make more flexible, or different control pts, etc.
// currently 5 x 13 track, multiply values to get bigger track
// currently, track spans the x,y plane, eventually span x,z plane?
void makeTrack() {
  Vector3 * start = new Vector3(-2.5f, 2.5f, 0.0f);
  Vector3 * middle1 = new Vector3(-2.5f, -2.5f, 0.0f);
  track->addCurve(new BCurve(start, 
                    new Vector3(-2.5f,  0.83f, 0.0f),
                    new Vector3(-2.5f,  -0.83f, 0.0f),
		    middle1));
  Vector3 * middle2 = new Vector3(2.5f, -2.5f, 0.0f);
  track->addCurve(new BCurve(middle1,
                    new Vector3(-2.5f, -6.5f, 0.0f),
                    new Vector3(2.5f, -6.5f, 0.0f),
		    middle2));
  Vector3 * end = new Vector3(2.5f, 2.5f, 0.0f);
  track->addCurve(new BCurve(middle2,
                   new Vector3(2.5f,  -0.83f, 0.0f),
		   new Vector3(2.5f, 0.83f, 0.0f),
		    end));
  track->addCurve(new BCurve(end,
	            new Vector3(2.5f, 6.5f, 0.0f),
		    new Vector3(-2.5f, 6.5f, 0.0f),
		    start));
}

void idleCallback(void)
{
  model.identity();
  model = model * mouse;
  if (mode) model = model * trackSize;
  displayCallback();  // call display routine to re-draw cube
}

void reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);
}

void displayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(model.getPointer());

  gluLookAt(cam.getEye()[0], cam.getEye()[1], cam.getEye()[2],
            cam.getCenter()[0], cam.getCenter()[1], cam.getCenter()[2],
            cam.getUp()[0], cam.getUp()[1], cam.getUp()[2]);

  if (mode) {
    track->drawTrack();
    track->drawRoadLines();
  } else {
    track->drawPoints(); 
    track->drawCurves();
  }
 
  glFlush();
  glutSwapBuffers();
}


void processKeys (unsigned char key, int x, int y) {
  if (key == 'r') {
    mouse.identity();
  }
  if (key == 'd') {
    if (mode) mode = false;
    else mode = true;
  }
  if (key == 't') {
    if (texture){
		texture = false;
		glDisable(GL_TEXTURE_2D); 
		track->texture = false;
    } else {
		texture = true;
		glEnable(GL_TEXTURE_2D); 
		track->texture = true;
    }
  }
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_UP:
      cam.setEye(track->getNext(0.01));
      cam.setCenter(track->getNext(0.01));
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_LEFT:
      //camera x + 1;
      break;
    case GLUT_KEY_RIGHT:
      //camera x - 1;
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
  mouse = mouse.trackballRotation(512,512,x,y,clickx,clicky);
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 0.0, -1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(width, height);      // set initial window size
  glutCreateWindow("OpenGL Cube for CSE167");    	      // open window and set window title
  
  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION);
  glDisable(GL_TEXTURE_2D);						// disable texture
  track->texture = false;

  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
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
  model.identity();
  mouse.identity(); 
  trackSize.identity();
  trackSize = Matrix4::scale(trackScale, trackScale, trackScale);
  makeTrack();
 
  loadTexture();

  glutMainLoop();
  return 0;
}

