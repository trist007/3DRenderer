#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include "display.h"

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

void int_swap(int* a, int* b);

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u32 color); 
void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u32 color);
void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u32 color);
void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u32 color);


#endif // TRIANGLE_H
