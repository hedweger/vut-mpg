#ifndef HOUSE_H_
#define HOUSE_H_
#define GL_SILENCE_DEPRECATION
#include "input.h"
#include <GLUT/glut.h>

class House {
public:
  House(float w, float d, float h, float doorW, float doorH);
  void draw(bool text);
  bool collides(Position_t pos, float r);

private:
  float width, depth, height;
  float doorWidth, doorHeight;
  GLuint texture[1];

  void genImg(void);
  void drawImg(bool text);
  void drawWalls(void);
  void drawDoor(void);
  void drawRoof(void);
};

#endif // HOUSE_H_
