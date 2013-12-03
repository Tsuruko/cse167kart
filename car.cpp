#include "car.h"

car::car(float size) {
  xpos = 0.0;
  trans.identity();
  trans = trans.translate(xpos, -1, -4);
  scale.identity();
  scale = scale.scale(0.5/size, 0.5/size, 0.5/size);
}

void car::draw(Matrix4 C) {
    Matrix4 carpos = C * scale * trans;
    glLoadMatrixf(carpos.getPointer());
    glDisable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_NORMAL_ARRAY);
    glEnable(GL_TEXTURE_2D);
}

void car::moveCar(GLfloat xtrans) {
  xpos += xtrans;
  if (xpos < -1.8) xpos = -1.8;
  if (xpos > 1.8) xpos = 1.8;
  trans = trans.translate(xpos, -1, -4);
}
