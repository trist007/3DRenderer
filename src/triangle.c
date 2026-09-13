#include "triangle.h"

void
draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u32 color)
{
  draw_line(x0, y0, x1, y1, color);
  draw_line(x1, y1, x2, y2, color);
  draw_line(x2, y2, x0, y0, color);
}

void
int_swap(int* a, int* b)
{
  int temp = *a;

  *a = *b;
  *b = temp;
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat bottom
///////////////////////////////////////////////////////////////////////////////
//
//        (x0,y0)
//          / \
//         /   \
//        /     \
//       /       \
//      /         \
//  (x1,y1)------(x2,y2)
//

void
fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u32 color)
{
  // Find the two slopes (two triangle legs)
  float inv_slope_1 = (float)(x1 - x0) / (y1 - y0); // x1 - x0 has lower y value so start with x1 as we increment y += 1
  float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

  // Start x_start and x_end from the top vertex (x0, y0)
  float x_start = x0;
  float x_end   = x0;

  // Loop all the scanlines from top to bottom
  for (int y = y0; y <= y2; y++)
  {
    draw_line(x_start, y, x_end, y, color);

    // NOTE(trist007): how much of a change in X as Y is incremented by 1 which is why we use inv_slope
    x_start += inv_slope_1;
    x_end   += inv_slope_2;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat top
///////////////////////////////////////////////////////////////////////////////
//
//  (x0,y0)------(x1,y1)
//      \         /
//       \       /
//        \     /
//         \   /
//          \ /
//        (x2,y2)
//

void
fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u32 color)
{
  // Find the two slopes (two triangle legs)
  float inv_slope_1 = (float)(x2 - x0) / (y2 - y0); // x2 - x0 has lower y so start with x2 cause we increment by Y += 1
  float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

  // Start x_start and x_end from the top vertex (x2, y2)
  float x_start = x2;
  float x_end   = x2;

  // Loop all the scanlines from bottom to top
  for (int y = y2; y >= y0; y--)
  {
    draw_line(x_start, y, x_end, y, color);

    // NOTE(trist007): how much of a change in X as Y is incremented by 1 which is why we use inv_slope
    x_start -= inv_slope_1;
    x_end   -= inv_slope_2;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled triangle with the flat-top/flat-bottom method
// We split the original triangle in two, half flat-bottom and half flat-top
///////////////////////////////////////////////////////////////////////////////
//
//          (x0,y0)
//            / \
//           /   \
//          /     \
//         /       \
//        /         \
//   (x1,y1)------(Mx,My)
//       \_           \
//          \_         \
//             \_       \
//                \_     \
//                   \    \
//                     \_  \
//                        \_\
//                           \
//                         (x2,y2)
//

void
draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u32 color)
{
  // We need to sort the vertices by y-coordinate ascending (y0 < y1 < y2)
  if (y0 > y1)
  {
    int_swap(&y0, &y1);
    int_swap(&x0, &x1);
  }

  if (y1 > y2)
  {
    int_swap(&y1, &y2);
    int_swap(&x1, &x2);
  }

  if (y0 > y1)
  {
    int_swap(&y0, &y1);
    int_swap(&x0, &x1);
  }

  // Calculate the new vertex (Mx, My) using triangle similarity
  int My = y1;
  int Mx = ((float)((x2 - x0) * (y1 - y0)) / (float)(y2 - y0)) + x0;

  // Fill flat bottom triangle
  fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);
  fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
}
