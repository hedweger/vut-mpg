#ifndef SUN_H_
#define SUN_H_

class Sun {
public:
  void draw(void);
  void update(int deltaMs);

private:
  static constexpr float periodMs = 300000.0f;
  float angle = 0.0f;
};

#endif
