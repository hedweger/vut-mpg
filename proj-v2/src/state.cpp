#include "state.h"
#include "cube.h"
#include "plane.h"
#include <GLUT/glut.h>
#include <iostream>

State::State() {
  game = GameState_t{.win_w = 800, .win_h = 600, .fullscreen = true};
  input = new InputHandler();
  sun = new Sun();
  lastMs = 0;
  frame_count = 0;
}

void State::idle(void) {}

void State::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  update();
  drawPlane(200.0f, 20);
  drawScaledCube(50, 40, 50, 30);
  sun->draw();

  if (++frame_count == 60) {
    input->idle();
    frame_count = 0;
  }

  glFlush();
  glutSwapBuffers();
}

void State::update() {
  int curr = glutGet(GLUT_ELAPSED_TIME);
  int deltaMs = curr - lastMs;
  lastMs = curr;

  input->update();
  sun->update(deltaMs);

  glutPostRedisplay();
}

void State::resize(int w, int h) {
  std::cout << "resize: " << w << "x" << h << std::endl;
  game.win_w = w;
  game.win_h = h;
  input->win_w = w;
  input->win_h = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (float)w / (float)h, 1, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}
