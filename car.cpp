#include "car.h"

car::car(float size) {
  xpos = 0.0;
  trans.identity();
  trans = trans.translate(xpos, -1, -4);
  firetrans1 = trans.translate(xpos + 0.2, -1, -2.5);
  firetrans2 = trans.translate(xpos - 0.2, -1, -2.5);
  scale.identity();
  scale = scale.scale(0.5/size, 0.5/size, 0.5/size);
  fire1 = new FireCone();
  fire2 = new FireCone();
}

void car::draw(Matrix4 C) {
  Matrix4 carpos = C * scale * trans;
  glLoadMatrixf(carpos.getPointer());
  glDisable(GL_TEXTURE_2D);
  glColor3f(1, 1, 1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);
  glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, indices);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_NORMAL_ARRAY);
  
  Matrix4 firepos = C * fire1->scale * firetrans1;
  glLoadMatrixf(firepos.getPointer());
  fire1->draw();
  firepos = C * fire2->scale * firetrans2;
  glLoadMatrixf(firepos.getPointer());
  fire2->draw();
  
  glEnable(GL_TEXTURE_2D);
}

void car::moveCar(GLfloat xtrans) {
  xpos += xtrans;
  if (xpos < -1.8) xpos = -1.8;
  if (xpos > 1.8) xpos = 1.8;
  trans = trans.translate(xpos, -1, -4);
  firetrans1 = trans.translate(xpos/1.1 + 0.2, -1, -2.5);
  firetrans2 = trans.translate(xpos/1.2 - 0.2, -1, -2.5);
}
