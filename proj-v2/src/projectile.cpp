#include "projectile.h"

Projectile::Projectile(const Position_t &startPos, const Position_t &dir, float speed)
{
  pos = startPos;
  velocity.x = dir.x * speed;
  velocity.y = dir.y * speed;
  velocity.z = dir.z * speed;
}

void Projectile::update(int deltaMs) {
  float dt = deltaMs / 1000.0f; 
  pos.x += velocity.x * dt;
  pos.y += velocity.y * dt + 0.5f * GRAVITY * dt * dt;
  pos.z += velocity.z * dt;
  velocity.y += GRAVITY * dt;
  lifeTime += dt;
}

void Projectile::draw() {
  glDisable(GL_LIGHTING);
  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(pos.x, pos.y, pos.z);
  glutSolidSphere(1.0, 12, 12);
  glPopMatrix();
  glEnable(GL_LIGHTING);
}

bool Projectile::isDead() {
  return pos.y < -5.0f || lifeTime > 10.0f;
}

