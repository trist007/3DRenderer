#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

typedef struct face_t face_t;
struct face_t {
  int a;
  int b;
  int c;
};

typedef struct triangle_t triangle_t;
struct triangle_t {
  vec2_t points[3];
};

#endif // TRIANGLE_H
