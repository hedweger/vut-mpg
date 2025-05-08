#include "state.h"
#include "plane.h"
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

State::State(void (*dt)(void)) {
  std::cout << "State init" << std::endl;
  game = GameState_t{.win_w = 800, .win_h = 600, .fullscreen = true};
  input = new InputHandler();
  sun = new Sun();
  house = new House(30.0f, 30.0f, 15.0f, 10.0f, 8.0f);
  cube = new Cube();
  river = new River(20.0f, planeSize, 200.0f, -100.0f, -200.0f, 200.0f);
  lastMs = 0;
  frame_count = 0;
  draw_tree = dt;

  std::cout << "State created" << std::endl; 
}

void State::idle(void) {}

void State::on_menu(int value) {
  switch (value) {
    case GameMenu_t::RESET_POS:
      input->reset();
      break;
    case GameMenu_t::FLASHLIGHT:
      input->flashlight = !input->flashlight;
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

void State::shoot() {
  Position_t start = input->camera.pos;
  Position_t dir = input->get_fwd();
  float speed = 50.0f;
  projectiles.push_back(new Projectile(start, dir, speed));
}


void State::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  input->draw_key();

  update();
  drawPlane(planeSize, 20);
  cube->draw(100, 10, 100, 30, en_textures);
  house->draw(en_textures);
  sun->draw();
  river->draw();
  this->draw_tree();
  for (Projectile *p : projectiles) {
    p->draw();
  }

  if (++frame_count == 60) {
    input->idle();
    frame_count = 0;
  }

  glDisable(GL_LIGHT1);
  glEnable(GL_LIGHT0);
  if (input->flashlight) {
    glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT0);
    input->toggle_flash();
  }


  glFlush();
  glutSwapBuffers();
}


void State::update() {
  int curr = glutGet(GLUT_ELAPSED_TIME);
  int deltaMs = curr - lastMs;
  lastMs = curr;

  for (Projectile *p : projectiles) {
    p->update(deltaMs);
  }
  projectiles.erase(
      std::remove_if(projectiles.begin(), projectiles.end(),
        [&](Projectile* p){
        if (p->isDead()) {
        delete p;
        return true;
        }
        return false;
        }),
      projectiles.end()
      );

  Position_t oldPos = input->camera.pos;
  input->compute_pos();
  Position_t newPos = input->camera.pos;

  Position_t testPos = {newPos.x, oldPos.y, oldPos.z};
  if (house->collides(testPos, camRadius)) {
    newPos.x = oldPos.x;
  }

  testPos = {newPos.x, oldPos.y, newPos.z};
  if (house->collides(testPos, camRadius)) {
    newPos.z = oldPos.z;
  }

  testPos = {newPos.x, newPos.y, newPos.z};
  if (house->collides(testPos, camRadius)) {
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
