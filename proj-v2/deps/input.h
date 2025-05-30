#ifndef INPUT_H_
#define INPUT_H_
#define PI 3.141592653589
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


typedef struct Position_t {
  double x, y, z;
} Position_t;

typedef struct Motion_t {
  int left, right, bwd, fwd, up, down, yleft, yright, pup, pdown;
} Motion_t;

typedef struct Camera_t {
  double pitch, yaw, roll;
  Position_t pos;
} Camera_t;

class InputHandler {
public:
  InputHandler();
  void dkey(unsigned char key, int x, int y);
  void ukey(unsigned char key, int x, int y);
  void pmouse(int x, int y);
  void mouse(int x, int y);
  void update(void);
  void compute_pos(void);
  void idle(void);
  void reset(void);
  void toggle_flash(void);
  void draw_key();
  Position_t get_fwd(void);

  int win_w, win_h;
  Camera_t camera;
  bool flashlight;

private:
  Position_t get_right(Position_t forward);
  static void normalize(Position_t *v);
  void warp_pointer(void);
 
  bool en_mouse;
  int oldx, oldy;
  Motion_t motion;
  Camera_t start;
  int activePoint;
  char last_key;

  static constexpr float SPEED = 0.5f;
  static constexpr float SENSITIVITY = 0.1f;
  const Position_t up = {0.0, 1.0, 0.0};
};

#endif // INPUT_H_
