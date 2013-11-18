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

int width  = 512;   // set window width in pixels here
int height = 512;   // set window height in pixels here

void idleCallback(void);
void reshapeCallback(int, int);
void displayCallback(void);

Track * track = new Track();

//just the DEFAULT track shape, no objects
//add params later to make more flexible, or different control pts, etc.
// currently 5 x 10 track, multiply values to get bigger track
// currently, track spans the x,y plane, eventually span x,z plane?
void makeTrack() {
  track->addCurve(new BCurve(Vector3(-2.5f, 2.5f, 0.0f),
                    Vector3(-2.5f, 6.5f , 0.0f),
                    Vector3(2.5f, 6.5f, 0.0f),
                    Vector3(2.5f, 2.5f, 0.0f)));
  track->addCurve(new BCurve(Vector3(2.5f, 2.5f, 0.0f),
                    Vector3(2.5f, 0.83f , 0.0f),
                    Vector3(2.5f, -0.83f, 0.0f),
                    Vector3(2.5f, -2.5f, 0.0f)));
  track->addCurve(new BCurve(Vector3(2.5f, -2.5f, 0.0f),
                    Vector3(2.5f, -6.5f , 0.0f),
                    Vector3(-2.5f, -6.5f, 0.0f),
                    Vector3(-2.5f, -2.5f, 0.0f)));
  track->addCurve(new BCurve(Vector3(-2.5f, -2.5f, 0.0f),
                    Vector3(-2.5f, -0.83f , 0.0f),
                    Vector3(-2.5f, 0.83f, 0.0f),
                    Vector3(-2.5f, 2.5f, 0.0f)));
}

void idleCallback(void)
{
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
  //glLoadMatrixd();

  glDisable(GL_LIGHTING);
  track->drawPoints(); 
  track->drawCurves();
  glEnable(GL_LIGHTING);
 
  glFlush();
  glutSwapBuffers();
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
 
  makeTrack(); 
 
  glutMainLoop();
  return 0;
}

