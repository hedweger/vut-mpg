#ifndef STATE_H_
#define STATE_H_
#include "input.h"
#include "sun.h"
#include <stdbool.h>

typedef struct GameState_t {
  int win_w;
  int win_h;
  bool fullscreen;
} GameState_t;

class State {
public:
  State();
  void display();
  void update();
  void resize(int w, int h);

  int lastMs = 0;
  GameState_t game;
  InputHandler *input;
  Sun *sun;
};

#endif // STATE_H_
