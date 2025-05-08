#ifndef CUBE_H_
#define CUBE_H_
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Cube {
public:
  void draw(float x, float y, float z, float size, bool texture);
  void genTexture(void);

private:
  GLuint codeTexture;
  void drawUnitCube(void);
};

#endif
