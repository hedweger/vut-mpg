#include "plane.h"
#include "colors.h"
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void drawPlane(float size, int div) {
  float step = size / div;
  float half = size / 2.0f;

  for (int i = 0; i < div; i++) {
    for (int j = 0; j < div; j++) {
      float x = -half + i * step;
      float z = -half + j * step;

      glBegin(GL_QUADS);
        glColor3f(grass.r, grass.g, grass.b);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(x, -5.0, z);
        glVertex3f(x + step, -5.0, z);
        glVertex3f(x + step, -5.0, z + step);
        glVertex3f(x, -5.0, z + step);
      glEnd();
    }
  }

  glBegin(GL_QUADS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(sky.r, sky.g, sky.b);
    glVertex3f(size/2.0f, -5.0f, -size/2.0f);
    glVertex3f(size/2.0f, -5.0f, size/2.0f);
    glVertex3f(size/2.0f, 15.0f, size/2.0f);
    glVertex3f(size/2.0f, 15.0f, -size/2.0f);

    glVertex3f(-size/2.0f, -5.0f, size/2.0f);
    glVertex3f(-size/2.0f, -5.0f, -size/2.0f);
    glVertex3f(-size/2.0f, 15.0f, -size/2.0f);
    glVertex3f(-size/2.0f, 15.0f, size/2.0f);

    glVertex3f(-size/2.0f, -5.0f, size/2.0f);
    glVertex3f(size/2.0f, -5.0f, size/2.0f);
    glVertex3f(size/2.0f, 15.0f, size/2.0f);
    glVertex3f(-size/2.0f, 15.0f, size/2.0f);

    glVertex3f(size/2.0f, -5.0f, -size/2.0f);
    glVertex3f(-size/2.0f, -5.0f, -size/2.0f);
    glVertex3f(-size/2.0f, 15.0f, -size/2.0f);
    glVertex3f(size/2.0f, 15.0f, -size/2.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
  glEnd();
}
