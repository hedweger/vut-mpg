#include "house.h"
#include "imageLoad.h"
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

House::House(float w, float d, float h, float doorW, float doorH)
    : width(w), depth(d), height(h), doorWidth(doorW), doorHeight(doorH) {}

void House::genImg(void) {
  if (!setTexture("/Users/hedweger/Vut/mgr-second/mpg/proj-v2/assets/img.bmp",
                  &texture[0], false)) {
    std::cout << "Chyba pri nacitani souboru" << std::endl;
    exit((int)0);
  }
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

bool House::collides(Position_t pos, float r) {
  float halfW = width * 0.5f;
  float halfD = depth * 0.5f;
  float minY = -5.0f;
  float maxY = height;

  // If we're within the door opening region, allow passage
  float doorXMin = -doorWidth * 0.5f + r;
  float doorXMax = doorWidth * 0.5f - r;
  float doorYMax = doorHeight - r;
  // Check if sphere around pos intersects the front opening
  if (pos.x > doorXMin && pos.x < doorXMax && pos.y > minY + r &&
      pos.y < doorYMax && pos.z < -halfD + r) {
    return false;
  }

  // Default box-collision against the house's bounding box
  // If inside inner box => no collision
  if (pos.x > -halfW + r && pos.x < halfW - r && pos.z > -halfD + r &&
      pos.z < halfD - r && pos.y > minY + r && pos.y < maxY - r) {
    return false;
  }

  // Find closest point on box
  float cx = std::fmax(-halfW, std::fmin(pos.x, halfW));
  float cy = std::fmax(minY, std::fmin(pos.y, maxY));
  float cz = std::fmax(-halfD, std::fmin(pos.z, halfD));

  float dx = pos.x - cx;
  float dy = pos.y - cy;
  float dz = pos.z - cz;

  return (dx * dx + dy * dy + dz * dz) < (r * r);
}

void House::draw(bool text) {
  drawImg(text);
  drawWalls();
  drawDoor();
  drawRoof();
}

void House::drawImg(bool text) {
  float halfW = width * 0.5f;
  float minY = -5.0f;
  float paintW = width * 0.2f;
  float paintH = height * 0.5f;
  float zCenter = 0.0f;
  float zMin = zCenter - paintW * 0.5f;
  float zMax = zCenter + paintW * 0.5f;
  float yBottom = minY + (height - minY) * 0.5f - paintH * 0.5f;
  float yTop = yBottom + paintH;
  float x = -halfW + 0.01f;

  if (text) {
    if (texture[0] == 0) {
      genImg();
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  } else {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.0f, 0.0f, 1.0f);
  }

  glNormal3f(-1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(x, yBottom, zMin);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x, yBottom, zMax);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x, yTop, zMax);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x, yTop, zMin);
  glEnd();

  if (text) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
  } else {
    glColor3f(1.0f, 1.0f, 1.0f);
  }
}

void House::drawWalls() {
  float halfW = width * 0.5f;
  float halfD = depth * 0.5f;
  float minY = -5.0f;
  // Window parameters (a simple empty square)
  float winSize = width * 0.2f;
  float winYBottom = minY + (height - minY) * 0.25f - winSize * 0.25f;
  float winYTop = winYBottom + winSize;
  float winZMin = -winSize * 0.5f;
  float winZMax = winSize * 0.5f;

  glBegin(GL_QUADS);
  // Floor
    glNormal3f(0,1,0);
  glColor3f(0.8f, 0.4f, 0.2f);
  glVertex3f(halfW, minY+0.1f, halfD);
  glVertex3f(-halfW, minY+0.1f, halfD);
  glVertex3f(-halfW, minY+0.1f, -halfD);
  glVertex3f(halfW, minY+0.1f, -halfD);
  glColor3f(1.0f, 1.0f, 1.0f);
  // Front wall left of door
  glNormal3f(0,0,-1);
  glVertex3f(-halfW, minY, -halfD);
  glVertex3f(-doorWidth * 0.5f, minY, -halfD);
  glVertex3f(-doorWidth * 0.5f, doorHeight, -halfD);
  glVertex3f(-halfW, doorHeight, -halfD);

  // Front wall right of door
  glVertex3f(doorWidth * 0.5f, minY, -halfD);
  glVertex3f(halfW, minY, -halfD);
  glVertex3f(halfW, doorHeight, -halfD);
  glVertex3f(doorWidth * 0.5f, doorHeight, -halfD);

  // Front wall above door
  glVertex3f(-halfW, doorHeight, -halfD);
  glVertex3f(halfW, doorHeight, -halfD);
  glVertex3f(halfW, height, -halfD);
  glVertex3f(-halfW, height, -halfD);

  // Back wall
    glNormal3f(0,0,1);
  glVertex3f(-halfW, minY, halfD);
  glVertex3f(halfW, minY, halfD);
  glVertex3f(halfW, height, halfD);
  glVertex3f(-halfW, height, halfD);

  // Left wall
    glNormal3f(-1,0,0);
  glVertex3f(-halfW, minY, -halfD);
  glVertex3f(-halfW, minY, halfD);
  glVertex3f(-halfW, height, halfD);
  glVertex3f(-halfW, height, -halfD);

  // Right wall with window opening
  glNormal3f(1, 0, 0);
  // Lower pane
  glVertex3f(halfW, minY, -halfD);
  glVertex3f(halfW, minY, halfD);
  glVertex3f(halfW, winYBottom, halfD);
  glVertex3f(halfW, winYBottom, -halfD);
  // Upper pane
  glVertex3f(halfW, winYTop, -halfD);
  glVertex3f(halfW, winYTop, halfD);
  glVertex3f(halfW, height, halfD);
  glVertex3f(halfW, height, -halfD);
  // Left side of window
  glVertex3f(halfW, winYBottom, -halfD);
  glVertex3f(halfW, winYBottom, winZMin);
  glVertex3f(halfW, winYTop, winZMin);
  glVertex3f(halfW, winYTop, -halfD);
  // Right side of window
  glVertex3f(halfW, winYBottom, winZMax);
  glVertex3f(halfW, winYBottom, halfD);
  glVertex3f(halfW, winYTop, halfD);
  glVertex3f(halfW, winYTop, winZMax);
  glEnd();
}

void House::drawDoor() {
  float halfD = depth * 0.5f;
  float minY = -5.0f;
  const float epsilon = 0.01f;
  float z = -halfD + epsilon;

  glColor3f(0.5f, 0.35f, 0.05f);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glVertex3f(-doorWidth * 0.5f, minY, z);
  glVertex3f(doorWidth * 0.5f, minY, z);
  glVertex3f(doorWidth * 0.5f, doorHeight, z);
  glVertex3f(-doorWidth * 0.5f, doorHeight, z);
  glEnd();
}

void House::drawRoof() {
  float halfW = width * 0.5f;
  float halfD = depth * 0.5f;
  float roofH = height * 0.5f;
  float peakY = height + roofH;

  glColor3f(0.8f, 0.1f, 0.1f);

  // Front triangle
  glBegin(GL_TRIANGLES);
  glNormal3f(0, 0, 1);
  glVertex3f(-halfW, height, halfD);
  glVertex3f(halfW, height, halfD);
  glVertex3f(0.0f, peakY, halfD);
  glEnd();

  // Back triangle
  glBegin(GL_TRIANGLES);
  glNormal3f(0, 0, -1);
  glVertex3f(halfW, height, -halfD);
  glVertex3f(-halfW, height, -halfD);
  glVertex3f(0.0f, peakY, -halfD);
  glEnd();

  // Right roof plane
  glBegin(GL_QUADS);
  {
    float ux = 0.0f - halfW, uy = peakY - height, uz = -halfD - halfD;
    float vx = 0.0f - halfW, vy = peakY - height, vz = halfD - (-halfD);
    float nx = uy * vz - uz * vy;
    float ny = uz * vx - ux * vz;
    float nz = ux * vy - uy * vx;
    glNormal3f(nx, ny, nz);
  }
  glVertex3f(halfW, height, halfD);
  glVertex3f(halfW, height, -halfD);
  glVertex3f(0.0f, peakY, -halfD);
  glVertex3f(0.0f, peakY, halfD);
  glEnd();

  // Left roof plane
  glBegin(GL_QUADS);
  {
    float ux = 0.0f + halfW, uy = peakY - height, uz = halfD - halfD;
    float vx = 0.0f + halfW, vy = peakY - height, vz = -halfD - halfD;
    float nx = uy * vz - uz * vy;
    float ny = uz * vx - ux * vz;
    float nz = ux * vy - uy * vx;
    glNormal3f(nx, ny, nz);
  }
  glVertex3f(-halfW, height, -halfD);
  glVertex3f(-halfW, height, halfD);
  glVertex3f(0.0f, peakY, halfD);
  glVertex3f(0.0f, peakY, -halfD);
  glEnd();
}
