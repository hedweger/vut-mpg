#ifndef STATE_H_
#define STATE_H_
#include "cube.h"
#include "house.h"
#include "input.h"
#include "sun.h"
#include <stdbool.h>

typedef struct GameState_t {
  int win_w;
  int win_h;
  bool fullscreen;
} GameState_t;

typedef enum GameMenu_t {
  RESET_POS,
  TOGGLE_ANIM,
  TOGGLE_TEXTURE,
  TOGGLE_SUN,
  EXIT,
} GameMenu_t;

class State {
public:
  State();
  void display();
  void update();
  void resize(int w, int h);
  void idle();
  void on_menu(int value);

  int lastMs = 0;
  int frame_count = 0;
  GameState_t game;
  InputHandler *input;
  Sun *sun;
  House *house;
  Cube *cube;

private:
  const float camRadius = 2.0f;
  bool en_textures = true;
  bool en_sun = true;
  bool en_anim = true;
};

#endif // STATE_H_
