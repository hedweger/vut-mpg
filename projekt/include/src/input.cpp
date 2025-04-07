#include "../hdr/input.h"
#include <GLUT/glut.h>
#include <math.h>

const float MOUSE_SENSITIVITY = 0.0025f;
const float PITCH_LIMIT = 1.5f;

float camX = 0.0f, camY = 1.8f, camZ = 5.0f;
float curX = 0.0f, curZ = -1.0f, curY = 0.0f;
int oldX = -1, oldY = -1;
float yaw = 0.0f;
float pitch = 0.0f;

bool mouseInitialized = false;
bool ignoreNextMouseWarp = false;

void handleMouseMovement(int x, int y) {
  int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
  int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

  if (ignoreNextMouseWarp) {
    ignoreNextMouseWarp = false;
    return;
  }
  if (!mouseInitialized) {
    oldX = x;
    oldY = y;
    mouseInitialized = true;
    return;
  }

  float sensitivity = 0.005f;
  int deltaX = x - oldX;
  int deltaY = y - oldY;
  yaw += deltaX * sensitivity;
  pitch -= deltaY * sensitivity;

  if (pitch > PITCH_LIMIT)
    pitch = PITCH_LIMIT;
  if (pitch < -PITCH_LIMIT)
    pitch = -PITCH_LIMIT;

  curX = cos(pitch) * sin(yaw);
  curY = sin(pitch);
  curZ = -cos(pitch) * cos(yaw);

  oldX = x;
  oldY = y;

  ignoreNextMouseWarp = true;
  glutWarpPointer(centerX, centerY);

  glutPostRedisplay();
}

void updateCamera() {
  float centerX = camX + curX;
  float centerY = camY + curY;
  float centerZ = camZ + curZ;

  gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);
}

void processSpecialKey(int key, int x, int y) {
  // TODO
}

void processKeys(unsigned char key, int x, int y) {
  float speed = 0.5f;
  float rightX = -curZ;
  float rightZ = curX;

  switch (key) {
  case 27:
    exit(0);
    break;
  case 'w':
    camX += curX * speed;
    camZ += curZ * speed;
    break;
  case 's':
    camX -= curX * speed;
    camZ -= curZ * speed;
    break;
  case 'a':
    // angleX -= 0.05f;
    camX -= rightX * speed;
    camZ -= rightZ * speed;
    // curX = sin(angle);
    // curZ = -cos(angle);
    break;
  case 'd':
    // angleX += 0.05f;
    camX += rightX * speed;
    camZ += rightZ * speed;
    // curX = sin(angle);
    // curZ = -cos(angle);
    break;
  }

  glutPostRedisplay();
}
