#include "input.h"
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <algorithm>

void InputHandler::normalize(Position_t *v) {
  double len = std::sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  if (len > 1e-6) {
    v->x /= len;
    v->y /= len;
    v->z /= len;
  }
}

void InputHandler::mouse(int x, int y) {
  glutPostRedisplay();
}


void InputHandler::reset() {
  camera = start;
  glutPostRedisplay();
}

void InputHandler::toggle_flash(void) {
  glEnable(GL_LIGHT1);
  GLfloat amb1[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat dif1[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat spec1[]= {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat pos1[] = {(float)camera.pos.x, (float)camera.pos.y, (float)camera.pos.z, 1.0f};
  double yawRad = camera.yaw * M_PI / 180.0;
  double pitchRad = camera.pitch * M_PI / 180.0;
  Position_t forward = {
    std::cos(pitchRad) * std::sin(yawRad),
    std::sin(pitchRad),
    -std::cos(pitchRad) * std::cos(yawRad)
  };
  GLfloat fwd1[] = {(float)forward.x, (float)forward.y, (float)forward.z};

  glLightfv(GL_LIGHT1, GL_AMBIENT,  amb1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  dif1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
  glLightfv(GL_LIGHT1, GL_POSITION, pos1);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, fwd1);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,   10.0f);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0f);
}

void InputHandler::idle(void) {}

Position_t InputHandler::get_fwd(void) {
  double yawRad = camera.yaw * M_PI / 180.0;
  double pitchRad = camera.pitch * M_PI / 180.0;
  Position_t forward = {
    std::cos(pitchRad) * std::sin(yawRad),
    std::sin(pitchRad),
    -std::cos(pitchRad) * std::cos(yawRad)
  };
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
void InputHandler::compute_pos() {
  Position_t forward = get_fwd();
  Position_t right = get_right(forward);
  if (motion.up) {
    camera.pos.y += SPEED;
    if (camera.pos.y > 100.0f) {
      camera.pos.y = 100.0f;
    }
  }
  if (motion.down) {
    camera.pos.y -= SPEED;
    if (camera.pos.y < 0.0f) {
      camera.pos.y = 0.0f;
    }
  }

  if (motion.yleft) {
    camera.yaw -= 1.0f;
  }
  if (motion.yright) {
    camera.yaw += 1.0f;
  }

  if (motion.pup) {
    camera.pitch -= 1.0f;
  }
  if (motion.pdown) {
    camera.pitch += 1.0f;
  }

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
}

void InputHandler::update() {
  Position_t forward = get_fwd();
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
  if (!en_mouse)
    return;

  int dx = (x - oldx);
  int dy = (y - oldy);

  oldx = x;
  oldy = y;
  camera.yaw = fmod(camera.yaw + dx * SENSITIVITY + 360.0, 360.0);
  camera.pitch = std::clamp(camera.pitch - dy * SENSITIVITY, -89.0, 89.0);
}

void InputHandler::draw_key() {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  glOrtho(0, w, 0, h, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glLoadIdentity();

  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  // glDisable(GL_DEPTH_TEST);   

  glColor3f(1.0f, 1.0f, 1.0f);
  float px = 30.0f;
  float py = h - 50.0f;
  glRasterPos2f(px, py);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, last_key);

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  // glEnable(GL_DEPTH_TEST);   
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
    case 'h':
    case 'q':
      motion.yleft = 1;
      break;
    case 'l':
    case 'e':
      motion.yright = 1;
      break;
    case 'k':
      motion.pup = 1;
      break;
    case 'j':
      motion.pdown = 1;
      break;
    case 'f':
      en_mouse = true;
      break;
    case 'r':
      flashlight = !flashlight;
      break;
    case 'F':
      en_mouse = !en_mouse;
      break;
    case '[':
      motion.up = 1;
      break;
    case ']':
      motion.down = 1;
      break;
    case 27:
      exit(0);
  }
  last_key = key;
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
    case 'h':
    case 'q':
      motion.yleft = 0;
      break;
    case 'l':
    case 'e':
      motion.yright = 0;
      break;
    case 'k':
      motion.pup = 0;
      break;
    case 'j':
      motion.pdown = 0;
      break;
    case 'f':
      en_mouse = false;
      break;
    case '[':
      motion.up = 0;
      break;
    case ']':
      motion.down = 0;
      break;
  }
}

InputHandler::InputHandler() {
  motion.left = 0;
  motion.right = 0;
  motion.fwd = 0;
  motion.bwd = 0;
  motion.up = 0;
  motion.down = 0;
  motion.yleft = 0;
  motion.yright = 0;
  motion.pup = 0;
  motion.pdown = 0;
  camera.pitch = 0;
  camera.yaw = 0;
  start = camera;
  win_w = glutGet(GLUT_WINDOW_WIDTH);
  win_h = glutGet(GLUT_WINDOW_HEIGHT);
}
