#include "river.h"
#include "colors.h"
#include <cmath>
#include <algorithm>
#include <vector>
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

River::River(float w, float planeSize, float ax, float az, float bx, float bz) {
  width = w;
  halfPlane = planeSize/2;
  aX = ax;
  aZ = az;
  bX = bx;
  bZ = bz;
}

void River::draw() {
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glColor3f(water.r, water.g, water.b);
  glBegin(GL_TRIANGLE_STRIP);

  const float dx = bX - aX;
  const float dz = bZ - aZ;
  const float len = std::sqrt(dx*dx + dz*dz);
  if (len < 1e-6f) {
    glEnd();
    glPopAttrib();
    return;
  }

  std::vector<float> ts;
  auto checkT = [&](float t){
    float x = aX + t*dx;
    float z = aZ + t*dz;
    if (x >= -halfPlane && x <= halfPlane &&
        z >= -halfPlane && z <= halfPlane)
      ts.push_back(t);
  };

  if (std::abs(dx) > 1e-6f) {
    checkT((-halfPlane - aX) / dx);
    checkT(( halfPlane - aX) / dx);
  }
  if (std::abs(dz) > 1e-6f) {
    checkT((-halfPlane - aZ) / dz);
    checkT(( halfPlane - aZ) / dz);
  }

  if (ts.size() < 2) {
    glEnd();
    return;
  }

  float tmin = *std::min_element(ts.begin(), ts.end());
  float tmax = *std::max_element(ts.begin(), ts.end());

  const float normX = -dz / len;
  const float normZ =  dx / len;
  const float halfW  = width * 0.5f;

  for (int i = 0; i <= segments; ++i) {
    float s = float(i) / segments;     
    float t = tmin + s * (tmax - tmin);

    float cx = aX + t*dx;
    float cz = aZ + t*dz;

    float wave = std::sin(s * 2.0f * M_PI) * halfW;
    cx += normX * wave;
    cz += normZ * wave;

    float y = -5.0f + 0.02f;  
    glVertex3f(cx + normX*halfW, y, cz + normZ*halfW);
    glVertex3f(cx - normX*halfW, y, cz - normZ*halfW);
  }

  glEnd();

  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
}
