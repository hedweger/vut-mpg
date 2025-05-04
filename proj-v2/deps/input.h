#ifndef INPUT_H_
#define INPUT_H_

typedef struct Position_t {
  double x, y, z;
} Position_t;

typedef struct Motion_t {
  int left, right, bwd, fwd;
} Motion_t;

typedef struct Camera_t {
  double pitch, yaw;
  Position_t pos;
} Camera_t;

class InputHandler {
public:
  InputHandler();
  void dkey(unsigned char key, int x, int y);
  void ukey(unsigned char key, int x, int y);
  void pmouse(int x, int y);
  void update(void);
  void idle(void);

  int win_w, win_h;

private:
  Position_t get_fwd(void);
  Position_t get_right(Position_t forward);
  static void normalize(Position_t *v);
  void warp_pointer(void);

  Motion_t motion;
  Camera_t camera;
  int last_x, last_y;
  bool just_warped = false;

  static constexpr float SPEED = 0.5f;
  static constexpr float SENSITIVITY = 0.1f;
  const Position_t up = {0.0, 1.0, 0.0};
};

#endif // INPUT_H_
