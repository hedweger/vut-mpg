#ifndef STATE_H_
#define STATE_H_
#include "cube.h"
#include "river.h"
#include "input.h"
#include "sun.h"
#include "house.h"
#include <stdbool.h>
#include "projectile.h"
#include <vector>

typedef struct GameState_t {
  int win_w;
  int win_h;
  bool fullscreen;
} GameState_t;

typedef enum GameMenu_t {
  RESET_POS,
  FLASHLIGHT,
  TOGGLE_TEXTURE,
  TOGGLE_SUN,
  EXIT,
} GameMenu_t;

class State {
public:
  State(void (*dt)(void));
  void display();
  void update();
  void resize(int w, int h);
  void idle();
  void on_menu(int value);
  void shoot(void);

  bool loaded;
  int lastMs = 0;
  int frame_count = 0;
  GameState_t game;
  InputHandler *input;
  Sun *sun;
  House *house;
  Cube *cube;
  River *river;
  void (*draw_tree)(void);

private:
  std::vector<Projectile*> projectiles;
  const float planeSize = 400.0f;
  const float camRadius = 2.0f;
  bool en_textures = true;
  bool en_sun = true;
  bool en_anim = true;
};

#endif // STATE_H_
