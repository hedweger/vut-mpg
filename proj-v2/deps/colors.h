#ifndef COLORS_H_
#define COLORS_H_

typedef struct frgb_t { 
  float r; 
  float g; 
  float b;
} frgb_t;

const frgb_t grass = {.r = 0.0f, .g = 0.7f, .b = 0.0f};
const frgb_t water = {.r = 0.0f, .g = 0.8f, .b = 0.8f};
const frgb_t sky   = {.r = 0.2f, .g = 0.6f, .b = 1.0f};

#endif
