#include "sun.h"
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>

void Sun::draw(void) {
  const float R = 400.0f;
  float rad = angle * M_PI / 180.0f;
  float x = R * std::cos(rad);
  float y = R * std::sin(rad);
  float z = 0.0f;

  GLfloat sunPos[] = {x, y, z, 1.0f};
  GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

  glDisable(GL_LIGHTING);
  glPushMatrix();
  glTranslatef(x, y, z);
  glColor3f(1.0f, 0.9f, 0.6f);
  glutSolidSphere(15.0, 16, 16);
  glPopMatrix();
  glEnable(GL_LIGHTING);
}

void Sun::update(int deltaMs) {
  float speed = 360.0f / periodMs;
  angle += speed * deltaMs;
  if (angle >= 360.0f)
    angle -= 360.0f;
}
