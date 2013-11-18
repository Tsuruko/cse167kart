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

using namespace std;

Matrix4 world;
Matrix4 mouse;  //for trackball rotating
//trackball capability
int clickx, clicky = 0;
bool lrb = true;

int width  = 512;   // set window width in pixels here
int height = 512;   // set window height in pixels here

void idleCallback(void);
void reshapeCallback(int, int);
void displayCallback(void);

Track * track = new Track();

//just the DEFAULT track shape, no objects
//add params later to make more flexible, or different control pts, etc.
// currently 5 x 13 track, multiply values to get bigger track
// currently, track spans the x,y plane, eventually span x,z plane?
void makeTrack() {
  Vector3 * start = new Vector3(-2.5f, 0.0f, 2.5f);
  Vector3 * middle1 = new Vector3(2.5f, 0.0f, 2.5f);
  track->addCurve(new BCurve(start,
             	    new Vector3(-2.5f, 0.0f, 6.5f ),
                    new Vector3(2.5f, 0.0f, 6.5f),
		    middle1));
  Vector3 * middle2 = new Vector3(2.5f, 0.0f, -2.5f);
  track->addCurve(new BCurve(middle1,
                    new Vector3(2.5f, 0.0f, 0.83f ),
                    new Vector3(2.5f, 0.0f, -0.83f),
		    middle2));
  Vector3 * end = new Vector3(-2.5f, 0.0f, -2.5f);
  track->addCurve(new BCurve(middle2,
                    new Vector3(2.5f, 0.0f, -6.5f ),
                    new Vector3(-2.5f, 0.0f, -6.5f),
		    end));
  track->addCurve(new BCurve(end,
                    new Vector3(-2.5f,  0.0f, -0.83f ),
                    new Vector3(-2.5f,  0.0f, 0.83f),
		    start));
}

void idleCallback(void)
{
  world.identity();
  world = world * mouse;
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
  glLoadMatrixf(world.getPointer());

  glDisable(GL_LIGHTING);
  track->drawPoints(); 
  track->drawCurves();
  glEnable(GL_LIGHTING);
 
  glFlush();
  glutSwapBuffers();
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

/*
  if (lrb) mouse = mouse.trackballRotation(512,512,x,y,clickx,clicky);
  else  {
  //currently doesn't work with this type of matrix/vector setup
    Vector4 s;
    if (clicky > y) s.set(1.1, 1.1, 1.1, 1);
    else if (clicky < y) s.set(.9, .9, .9, 1);
    else s.set(1,1,1,1);
    mouse.scale(s);
  }
*/
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
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

  world.identity();
  mouse.identity(); 
  makeTrack(); 
 
  glutMainLoop();
  return 0;
}

