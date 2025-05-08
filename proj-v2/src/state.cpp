#include "state.h"
#include "cube.h"
#include "house.h"
#include "plane.h"
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>

State::State() {
  std::cout << "State init" << std::endl;
  game = GameState_t{.win_w = 800, .win_h = 600, .fullscreen = true};
  input = new InputHandler();
  sun = new Sun();
  house = new House(30.0f, 30.0f, 15.0f, 10.0f, 8.0f);
  cube = new Cube();
  lastMs = 0;
  frame_count = 0;
  std::cout << "State created" << std::endl;
}

void State::idle(void) {}

void State::on_menu(int value) {
  switch (value) {
  case GameMenu_t::RESET_POS:
    input->reset();
    break;
  case GameMenu_t::TOGGLE_ANIM:
    en_anim = !en_anim;
    std::cout << "en_anim: " << en_anim << std::endl;
    break;
  case GameMenu_t::TOGGLE_TEXTURE:
    en_textures = !en_textures;
    if (en_textures)
      glEnable(GL_TEXTURE_2D);
    else
      glDisable(GL_TEXTURE_2D);
    break;
  case GameMenu_t::TOGGLE_SUN:
    en_sun = !en_sun;
    break;
  case GameMenu_t::EXIT:
    std::exit(0);
  }
}

void State::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  update();
  drawPlane(400.0f, 20);
  cube->draw(100, 10, 100, 30, en_textures);
  house->draw(en_textures);
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

  Position_t oldPos = input->camera.pos;
  input->compute_pos();
  Position_t newPos = input->camera.pos;

  Position_t testPos = {newPos.x, oldPos.y, oldPos.z};
  if (house->collides(testPos, camRadius)) {
    std::cout << "coliding on x!" << std::endl;
    newPos.x = oldPos.x;
  }

  testPos = {newPos.x, oldPos.y, newPos.z};
  if (house->collides(testPos, camRadius)) {
    std::cout << "coliding on z!" << std::endl;
    newPos.z = oldPos.z;
  }

  testPos = {newPos.x, newPos.y, newPos.z};
  if (house->collides(testPos, camRadius)) {
    std::cout << "coliding on y!" << std::endl;
    newPos.y = oldPos.y;
  }

  input->camera.pos = newPos;
  input->update();

  if (en_sun)
    sun->update(deltaMs);
  glutPostRedisplay();
}

void State::resize(int w, int h) {
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
