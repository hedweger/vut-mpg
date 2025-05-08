#ifndef PROJECTILE_H_
#define PROJECTILE_H_
#include "input.h"  
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class Projectile {
public:
    Projectile(const Position_t &startPos, const Position_t &dir, float speed);
    ~Projectile() = default;
    void update(int deltaMs);
    void draw();
    bool isDead();

private:
    Position_t pos;
    Position_t velocity;
    static constexpr float GRAVITY = -9.81f; 
    float lifeTime = 0.0f;
};

#endif // PROJECTILE_H_

