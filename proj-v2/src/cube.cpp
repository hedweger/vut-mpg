#include "cube.h"
#include <GLUT/glut.h>

void drawScaledCube(float x, float y, float z, float size) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(size, size, size);
  glColor3f(1.0f, 0.0f, 0.0f);
  drawUnitCube();
  glPopMatrix();
}

void drawUnitCube(void) {
  glBegin(GL_TRIANGLES);

  // Front face (z = 0.5)
  glNormal3f(0.0f, 0.0f, 1.0f);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);

  glVertex3f(-0.5f, -0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glVertex3f(-0.5f, 0.5f, 0.5f);

  // Back face (z = -0.5)
  glNormal3f(0.0f, 0.0f, -1.0f);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(-0.5f, 0.5f, -0.5f);

  glVertex3f(0.5f, -0.5f, -0.5f);
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);

  // Left face (x = -0.5)
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  glVertex3f(-0.5f, 0.5f, 0.5f);

  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(-0.5f, 0.5f, 0.5f);
  glVertex3f(-0.5f, 0.5f, -0.5f);

  // Right face (x = 0.5)
  glNormal3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);

  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);

  // Top face (y = 0.5)
  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-0.5f, 0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);

  glVertex3f(-0.5f, 0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glVertex3f(-0.5f, 0.5f, -0.5f);

  // Bottom face (y = -0.5)
  glNormal3f(0.0f, -1.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);

  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(-0.5f, -0.5f, 0.5f);

  glEnd();
}
