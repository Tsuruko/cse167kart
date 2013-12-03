#include "car.h"

car::car() {
  trans = Matrix4::translate(0, -1, -4);
  scale = Matrix4::scale(0.5, 0.5, 0.5);
}

void car::draw(Matrix4 C) {
    glMatrixMode(GL_MODELVIEW);
    Matrix4 Cnew = C * scale;
    glLoadMatrixf(Cnew.getPointer());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_NORMAL_ARRAY);
    glEnable(GL_TEXTURE_2D);
}

