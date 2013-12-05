#include "car.h"

car::car(float size) {
  t = 0.2;
  curve = 0;
  xpos = 0.0;
  forwardTrans.identity();
  sideTrans.identity();
  scale.identity();
  scale = scale.scale(0.5/size, 0.5/size, 0.5/size);
}

void car::draw(Matrix4 C) {
  Matrix4 carpos = C * forwardTrans * scale * sideTrans;
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
  glEnable(GL_TEXTURE_2D);
}

void car::moveSide(GLfloat xtrans) {
  xpos += xtrans;
  if (xpos < -1.8) xpos = -1.8;
  if (xpos > 1.8) xpos = 1.8;
  sideTrans = Matrix4::translate(xpos, -1, -4);
}

void car::moveForward(Vector3 v) {
  forwardTrans = Matrix4::translate(v[0], v[1], v[2]);
}
