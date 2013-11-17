#include <stdlib.h>
#include <math.h>   // include math functions, such as sin, cos, M_PI
#include <iostream> // allow c++ style console printouts
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "BCurve.h"

BCurve *curve1 = new BCurve(Vector3(3.0f, 3.0f, 0.0f),
                    Vector3(2.0f, 2.0f , 0.0f),
                    Vector3(3.0f, 1.0f, 0.0f),
                    Vector3(2.0f, 0.0f, 0.0f));

BCurve *curve2 = new BCurve(Vector3(2.0f, 0.0f, 0.0f),
                    Vector3(1.0f, -1.0f , 0.0f),
                    Vector3(0.1f, -2.0f, 0.0f),
                    Vector3(2.0f, -3.0f, 0.0f));

BCurve *selectedCurve;

bool texOn = false;
int mouseX;
int mouseY;
int mouseButton;
int selected;

GLfloat stacks = 0.05;
int slices = 10;

using namespace std; // allow console printouts without std::

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);
/*! GLUT idle callback function */
void idle();

void drawSurfaceOfRevolution(BCurve *curve, GLfloat offset)
{
  Vector3 v1, v2, n1, n2;
  Vector4 test1, test2, test3, test4;
  Matrix4 r;
  
  for (GLfloat i = 0; i < 1; i += stacks)
  {
    glBegin(GL_QUAD_STRIP);
    for(int angle = 0; angle <= 360; angle += slices)
    {
      r = Matrix4::rotateY(angle);
      v1 = Vector3(curve->getPoint(i)[0], curve->getPoint(i)[1], 0);
      v2 = Vector3(curve->getPoint(i + stacks)[0], curve->getPoint(i + stacks)[1], 0);
      n1 = Vector3(-curve->getTangent(i)[1], curve->getTangent(i)[0], 0);
      n2 = Vector3(-curve->getTangent(i + stacks)[1], curve->getTangent(i + stacks)[0], 0);
      
      n1.normalize();
      n2.normalize();
      
      test1 = Vector4(v1[0], v1[1], v1[2], 1);
      test2 = Vector4(v2[0], v2[1], v2[2], 1);
      test3 = Vector4(n1[0], n1[1], n1[2], 1);
      test4 = Vector4(n2[0], n2[1], n2[2], 1);
      
      test1 = r * test1;
      test2 = r * test2;
      test3 = r * test3;
      test4 = r * test4;
      
      v1 = Vector3(test1[0], test1[1], test1[2]);
      v2 = Vector3(test2[0], test2[1], test2[2]);
      n1 = Vector3(test3[0], test3[1], test3[2]);
      n2 = Vector3(test4[0], test4[1], test4[2]);
      
      glNormal3fv(n1.getPointer());
      glTexCoord2f(angle/360.0, i/2.0 + offset);
      glVertex3fv(v1.getPointer());
      glNormal3fv(n2.getPointer());
      glTexCoord2f(angle/360.0, (i + stacks)/2.0 + offset);
      glVertex3fv(v2.getPointer());
    };
    glEnd();
  }
}

/** Load a ppm file from disk.
 @input filename The location of the PPM file.  If the file is not found, an error message
 will be printed and this function will return 0
 @input width This will be modified to contain the width of the loaded image, or 0 if file not found
 @input height This will be modified to contain the height of the loaded image, or 0 if file not found
 @return Returns the RGB pixel data as interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
 **/
unsigned char* loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;
  
	if ( (fp=fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}
  
	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);
  
	// Read width and height:
	do
	{
		retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width  = atoi(buf[1]);
	height = atoi(buf[2]);
  
	// Read maxval:
	do
	{
	  retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
  
	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}
  
	return rawData;
}

// initialize OpenGL state
void initGL()
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 0.0, -1.0, 0.0};	// lightsource position
  
  //glEnable(GL_TEXTURE_2D);   // enable texture mapping
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
}

// load image file into texture object
void loadTexture()
{
  GLuint texture[1];     // storage for one texture
  int twidth, theight;   // texture width/height [pixels]
  unsigned char* tdata;  // texture pixel data
  
  // Load image file
  tdata = loadPPM("brickwall.ppm", twidth, theight);
  if (tdata==NULL) return;
  
  // Create ID for texture
  glGenTextures(1, &texture[0]);
  
  // Set this texture to be the one we are working with
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  
  // Generate the texture
  glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
  
  // Make sure no bytes are padded:
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  // Select GL_MODULATE to mix texture with quad color for shading:
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
  // Use bilinear interpolation:
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
    case 't':
      texOn = !texOn;
      break;
	}
}

void mousePress(int button, int state, int x, int y)
{
  for (int i = 0; i < 4; i++) {
    GLfloat cpx = curve1->getCPointer(i)[0];
    GLfloat cpy = curve1->getCPointer(i)[1];
    if (((x - 256) / 64.0) < cpx + 0.2 && ((x - 256) / 64.0) > cpx - 0.2 && -(y/64.0) + 4 < cpy + 0.2 && -(y/64.0) + 4 > cpy - 0.2) {
      selectedCurve = curve1;
      selected = i;
      break;
    }
    cpx = curve2->getCPointer(i)[0];
    cpy = curve2->getCPointer(i)[1];
    if (((x - 256) / 64.0) < cpx + 0.2 && ((x - 256) / 64.0) > cpx - 0.2 && -(y/64.0) + 4 < cpy + 0.2 && -(y/64.0) + 4 > cpy - 0.2) {
      selectedCurve = curve2;
      selected = i;
      break;
    }
  }
  mouseButton = button;
}

void mouseMotion(int x, int y)
{
  switch(mouseButton) {
    case GLUT_LEFT_BUTTON:
      if (((selectedCurve == curve1 && selected == 3) || (selectedCurve == curve2 && selected == 0)) && x > 256) {
        curve1->setCP(3, 0, ((x - 256) / 64.0));
        curve1->setCP(3, 1, -(y/64.0) + 4);
        curve2->setCP(0, 0, ((x - 256) / 64.0));
        curve2->setCP(0, 1, -(y/64.0) + 4);
      }
      else if (x > 256)
      {
        selectedCurve->setCP(selected, 0, ((x - 256) / 64.0));
        selectedCurve->setCP(selected, 1, -(y/64.0) + 4);
      }
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  
  /* set the window size to 512 x 512 */
  glutInitWindowSize(512, 512);
  
  /* set the display mode to Red, Green, Blue and Alpha
   allocate a depth buffer
   enable double buffering
   */
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  
  /* create the window */
  glutCreateWindow("Texturing Example");
  
  /* set the glut display callback function
   this is the function GLUT will call every time
   the window needs to be drawn
   */
  glutDisplayFunc(display);
  
  /* set the glut reshape callback function
   this is the function GLUT will call whenever
   the window is resized, including when it is
   first created
   */
  glutReshapeFunc(reshape);
  
  glutIdleFunc(idle);
  
  glutKeyboardFunc(processNormalKeys);
  
  glutMouseFunc(mousePress);
  glutMotionFunc(mouseMotion);
  
  loadTexture();
  
  initGL();
  
  /* enter the main event loop so that GLUT can process
   all of the window event messages
   */
  glutMainLoop();
  
  return 0;
}

/*! glut display callback function.  Every time the window needs to be drawn,
 glut will call this function.  This includes when the window size
 changes, or when another window covering part of this window is
 moved so this window is uncovered.
 */
void display()
{
  cerr << "display callback" << endl;
  
  /* clear the color buffer (resets everything to black) */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glDisable(GL_LIGHTING);
  glColor3f(1, 1, 1);
  glBegin(GL_LINES);
  glVertex3f(0, 10, 0);
  glVertex3f(0, -10, 0);
  glEnd();
  glEnable(GL_LIGHTING);
  
  glColor3f(1, 1, 1);
  if (texOn) {
    glEnable(GL_TEXTURE_2D);
  }
  drawSurfaceOfRevolution(curve1, 0);
  drawSurfaceOfRevolution(curve2, 0.5);
  glDisable(GL_TEXTURE_2D);
  
  glDisable(GL_LIGHTING);
  glPointSize(10);
  glColor3f(0, 0, 1);
  glBegin(GL_POINTS);
  for (GLfloat i = 0; i < 4; i += 0.01)
  {
    glVertex3fv(curve1->getCPointer(i));
    glVertex3fv(curve2->getCPointer(i));
  }
  glEnd();
  
  glColor3f(1, 0, 0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < 4; i++) {
    glVertex3f(curve1->getCP(i)[0], curve1->getCP(i)[1], -3.4);
  }
  for (int i = 0; i < 4; i++) {
    glVertex3f(curve2->getCP(i)[0], curve2->getCP(i)[1], -3.4);
  }
  glEnd();
  
  glColor3f(0, 1, 0);
  glBegin(GL_LINE_STRIP);
  for (GLfloat i = 0; i <= 1; i += stacks) {
    glVertex3f(curve1->getPoint(i)[0], curve1->getPoint(i)[1], -3.5);
  }
  for (GLfloat i = 0; i <= 1; i += stacks) {
    glVertex3f(curve2->getPoint(i)[0], curve2->getPoint(i)[1], -3.5);
  }
  glEnd();
  glEnable(GL_LIGHTING);
  
  /* swap the back and front buffers so we can see what we just drew */
  glutSwapBuffers();
}

/*! glut reshape callback function.  GLUT calls this function whenever
 the window is resized, including the first time it is created.
 You can use variables to keep track the current window size.
 */
void reshape(int width, int height)
{
  cerr << "reshape callback" << endl;
  
  /* tell OpenGL we want to display in a recangle that is the
   same size as the window
   */
  glViewport(0,0,width,height);
  
  /* switch to the projection matrix */
  glMatrixMode(GL_PROJECTION);
  
  /* clear the projection matrix */
  glLoadIdentity();
  
  /* set the camera view, orthographic projection with 4x4 unit square canvas*/
  glOrtho(-4,4,-4,4,4,-4);
  
  /* switch back to the model view matrix */
  glMatrixMode(GL_MODELVIEW);
}

/* Gets called whenever computer doesn't have anything else to do */
void idle()
{
  cerr << "idle callback" << endl;
  display();     // call display callback, useful for animation
}