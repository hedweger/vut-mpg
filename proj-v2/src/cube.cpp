#include "cube.h"
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <vector>

// Build a 64×64 black-&-white checker and upload it after GL context exists
void Cube::genTexture() {
  const int size = 64;
  std::vector<unsigned char> data(size * size * 3);
  for (int y = 0; y < size; ++y) {
    for (int x = 0; x < size; ++x) {
      int idx = (y * size + x) * 3;
      // 8×8 blocks: pure white or pure black
      bool even = (((x / 8) + (y / 8)) & 1) == 0;
      unsigned char c = even ? 255 : 0;
      data[idx + 0] = c; // R
      data[idx + 1] = c; // G
      data[idx + 2] = c; // B
    }
  }

  glGenTextures(1, &codeTexture);
  glBindTexture(GL_TEXTURE_2D, codeTexture);
  // Nearest-neighbor to keep crisp edges
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data.data());
  glBindTexture(GL_TEXTURE_2D, 0);
}

// Position & scale, then bind texture or color and draw
void Cube::draw(float x, float y, float z, float size, bool texture) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(size, size, size);

  if (texture) {
    genTexture();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, codeTexture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  } else {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 0.0f, 0.0f);
  }

  drawUnitCube();
  if (texture) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
  }
  glPopMatrix();
}

// Six quads, each with full [0..1] texcoords and proper normals
void Cube::drawUnitCube() {
  glBegin(GL_QUADS);
  // Front (Z+)
  glNormal3f(0, 0, 1);
  glTexCoord2f(0, 0);
  glVertex3f(-.5f, -.5f, .5f);
  glTexCoord2f(1, 0);
  glVertex3f(.5f, -.5f, .5f);
  glTexCoord2f(1, 1);
  glVertex3f(.5f, .5f, .5f);
  glTexCoord2f(0, 1);
  glVertex3f(-.5f, .5f, .5f);

  // Back (Z-)
  glNormal3f(0, 0, -1);
  glTexCoord2f(0, 0);
  glVertex3f(.5f, -.5f, -.5f);
  glTexCoord2f(1, 0);
  glVertex3f(-.5f, -.5f, -.5f);
  glTexCoord2f(1, 1);
  glVertex3f(-.5f, .5f, -.5f);
  glTexCoord2f(0, 1);
  glVertex3f(.5f, .5f, -.5f);

  // Left (X-)
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-.5f, -.5f, -.5f);
  glTexCoord2f(1, 0);
  glVertex3f(-.5f, -.5f, .5f);
  glTexCoord2f(1, 1);
  glVertex3f(-.5f, .5f, .5f);
  glTexCoord2f(0, 1);
  glVertex3f(-.5f, .5f, -.5f);

  // Right (X+)
  glNormal3f(1, 0, 0);
  glTexCoord2f(0, 0);
  glVertex3f(.5f, -.5f, .5f);
  glTexCoord2f(1, 0);
  glVertex3f(.5f, -.5f, -.5f);
  glTexCoord2f(1, 1);
  glVertex3f(.5f, .5f, -.5f);
  glTexCoord2f(0, 1);
  glVertex3f(.5f, .5f, .5f);

  // Top (Y+)
  glNormal3f(0, 1, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-.5f, .5f, .5f);
  glTexCoord2f(1, 0);
  glVertex3f(.5f, .5f, .5f);
  glTexCoord2f(1, 1);
  glVertex3f(.5f, .5f, -.5f);
  glTexCoord2f(0, 1);
  glVertex3f(-.5f, .5f, -.5f);

  // Bottom (Y-)
  glNormal3f(0, -1, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-.5f, -.5f, -.5f);
  glTexCoord2f(1, 0);
  glVertex3f(.5f, -.5f, -.5f);
  glTexCoord2f(1, 1);
  glVertex3f(.5f, -.5f, .5f);
  glTexCoord2f(0, 1);
  glVertex3f(-.5f, -.5f, .5f);
  glEnd();
}
