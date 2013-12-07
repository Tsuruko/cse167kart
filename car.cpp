#include "car.h"

car::car(float size) {
  t = 0.06;
  curve = 0;
  xpos = 0.0;
  zpos = 0.0;
  scale.set(.8/size, .8/size, .8/size);
}

void car::draw(Matrix4 model, Matrix4 cam) {
  glMatrixMode(GL_MODELVIEW);

//move the car
  glTranslatef(forwardTrans[0], forwardTrans[1], forwardTrans[2]);  
  glScalef(scale[0], scale[1], scale[2]);
  glTranslatef(0.0, 0.0, zpos);

//orient the car to face the right direction
  glRotatef(90, 1.0, 0.0, 0.0);
  glRotatef(180, 0.0, 1.0, 0.0);

//hacky adjustments of rotation
  if (curve%2 == 1) glRotatef(180*t, 0.0, 1.0, 0.0);
  if (curve > 1) glRotatef(180, 0.0, 1.0, 0.0);
  //glRotatef(prevT.angle(forwardTrans)*2, 1.0, 0.0, 0.0);
  float check = prevT[2] - forwardTrans[2];
  glRotatef(-check*600, 1.0, 0.0, 0.0);

  glTranslatef(xpos, 0.0, 0.0);

  glDisable(GL_TEXTURE_2D);
  glColor3f(1, 1, 1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);
  glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, indices);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_NORMAL_ARRAY);
  glEnable(GL_TEXTURE_2D);
}

void car::moveSide(GLfloat xtrans) {
  xpos += xtrans;
  if (xpos < -3.7) xpos = -3.7;
  if (xpos > 3.7) xpos = 3.7;
}

void car::moveForward(Vector3 v) {
  prevT = forwardTrans;
  forwardTrans = v;
}

void car::findMinMax() {
  int j = 0;
  for (int i = 0; i < nVerts; i++) {
    j = i * 3;
    if (vertices[j] > xmax) {
      xmax = vertices[j];
    } else if (vertices[j] < xmin) {   
      xmin = vertices[j];
    }
    if (vertices[j+1] > ymax) {
      ymax = vertices[j+1];
    } else if (vertices[j+1] < ymin) {
      ymin = vertices[j+1];
    }
    if (vertices[j+2] > zmax) {
      zmax = vertices[j+2];
    } else if (vertices[j+2] < zmin) {
      zmin = vertices[j+2];
    } 
  }
  zpos = 0.3 + scale[2]*(zmax-zmin);
}
