#include "plane.h"
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

void drawPlane(float size, int div) {
  float step = size / div;
  float half = size / 2.0f;

  for (int i = 0; i < div; i++) {
    for (int j = 0; j < div; j++) {
      float x = -half + i * step;
      float z = -half + j * step;

      glBegin(GL_QUADS);
      glColor3f(0.5f, 0.5f, 0.5f);
      glNormal3f(0.0f, 1.0f, 0.0f);
      glVertex3f(x, -5.0, z);
      glVertex3f(x + step, -5.0, z);
      glVertex3f(x + step, -5.0, z + step);
      glVertex3f(x, -5.0, z + step);
      glEnd();
    }
  }
}
