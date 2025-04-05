#include "input.h"
#include <GLUT/glut.h>
#include <math.h>

float camX = 0.0f, camY = 1.8f, camZ = 5.0f;
float dirX = 0.0f, dirZ = -1.0f, dirY = 0.0f;

int lastMouseX = -1;
int lastMouseY = -1;
bool mouseInitialized = false;
bool ignoreNextMouseWarp = false;

float yaw = 0.0f;
float pitch = 0.0f;

const float MOUSE_SENSITIVITY = 0.0025f;
const float PITCH_LIMIT = 1.5f;

void handleMouseMovement(int x, int y) {
  int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
  int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

  if (ignoreNextMouseWarp) {
    ignoreNextMouseWarp = false;
    return;
  }
  if (!mouseInitialized) {
    lastMouseX = x;
    lastMouseY = y;
    mouseInitialized = true;
    return;
  }

  float sensitivity = 0.005f;
  int deltaX = x - lastMouseX;
  int deltaY = y - lastMouseY;
  yaw += deltaX * sensitivity;
  pitch -= deltaY * sensitivity;

  if (pitch > PITCH_LIMIT)
    pitch = PITCH_LIMIT;
  if (pitch < -PITCH_LIMIT)
    pitch = -PITCH_LIMIT;

  dirX = cos(pitch) * sin(yaw);
  dirY = sin(pitch);
  dirZ = -cos(pitch) * cos(yaw);

  lastMouseX = x;
  lastMouseY = y;

  ignoreNextMouseWarp = true;
  glutWarpPointer(centerX, centerY);

  glutPostRedisplay();
}

void updateCamera() {
  float centerX = camX + dirX;
  float centerY = camY + dirY;
  float centerZ = camZ + dirZ;

  gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);
}

void processSpecialKey(int key, int x, int y) {
  // TODO
}

void processKeys(unsigned char key, int x, int y) {
  float speed = 0.5f;
  float rightX = -dirZ;
  float rightZ = dirX;

  switch (key) {
  case 27:
    exit(0);
    break;
  case 'w':
    camX += dirX * speed;
    camZ += dirZ * speed;
    break;
  case 's':
    camX -= dirX * speed;
    camZ -= dirZ * speed;
    break;
  case 'a':
    // angleX -= 0.05f;
    camX -= rightX * speed;
    camZ -= rightZ * speed;
    // dirX = sin(angle);
    // dirZ = -cos(angle);
    break;
  case 'd':
    // angleX += 0.05f;
    camX += rightX * speed;
    camZ += rightZ * speed;
    // dirX = sin(angle);
    // dirZ = -cos(angle);
    break;
  }

  glutPostRedisplay();
}
