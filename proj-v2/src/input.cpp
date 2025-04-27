#include "input.h"
#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

void InputHandler::normalize(Position_t *v) {
  double len = std::sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  if (len > 1e-6) {
    v->x /= len;
    v->y /= len;
    v->z /= len;
  }
}

Position_t InputHandler::get_fwd(void) {
  double yawRad = camera.yaw * M_PI / 180.0;
  double pitchRad = camera.pitch * M_PI / 180.0;
  Position_t forward = {std::cos(pitchRad) * std::sin(yawRad),
                        std::sin(pitchRad),
                        -std::cos(pitchRad) * std::cos(yawRad)};
  normalize(&forward);
  return forward;
}

Position_t InputHandler::get_right(Position_t forward) {
  Position_t right = {forward.y * up.z - forward.z * up.y,
                      forward.z * up.x - forward.x * up.z,
                      forward.x * up.y - forward.y * up.x};
  normalize(&right);
  return right;
}

void InputHandler::update() {
  Position_t forward = get_fwd();
  Position_t right = get_right(forward);
  if (motion.fwd) {
    camera.pos.x += forward.x * SPEED;
    camera.pos.z += forward.z * SPEED;
  }
  if (motion.bwd) {
    camera.pos.x -= forward.x * SPEED;
    camera.pos.z -= forward.z * SPEED;
  }
  if (motion.right) {
    camera.pos.x += right.x * SPEED;
    camera.pos.z += right.z * SPEED;
  }
  if (motion.left) {
    camera.pos.x -= right.x * SPEED;
    camera.pos.z -= right.z * SPEED;
  }

  std::cout << "pitch: " << camera.pitch << " yaw: " << camera.yaw << std::endl;
  std::cout << "x: " << camera.pos.x << " y: " << camera.pos.y
            << " z: " << camera.pos.z << std::endl;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, // eyes
            camera.pos.x + forward.x,                 // x position
            camera.pos.y + forward.y,                 // y position
            camera.pos.z + forward.z,                 // z position
            up.x, up.y, up.z                          // up
  );
}

void InputHandler::pmouse(int x, int y) {
  camera.yaw = x * SENSITIVITY;
  camera.pitch = -y * SENSITIVITY;
  if (camera.pitch < -89)
    camera.pitch = -89;
  else if (camera.pitch > 89)
    camera.pitch = 89;
}

void InputHandler::dkey(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    motion.fwd = 1;
    break;
  case 's':
    motion.bwd = 1;
    break;
  case 'a':
    motion.left = 1;
    break;
  case 'd':
    motion.right = 1;
    break;
  case 27:
    exit(0);
  }
}

void InputHandler::ukey(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    motion.fwd = 0;
    break;
  case 's':
    motion.bwd = 0;
    break;
  case 'a':
    motion.left = 0;
    break;
  case 'd':
    motion.right = 0;
    break;
  }
}

InputHandler::InputHandler() {
  motion.left = 0;
  motion.right = 0;
  motion.fwd = 0;
  motion.bwd = 0;
  camera.pitch = 0;
  camera.yaw = 0;
}
