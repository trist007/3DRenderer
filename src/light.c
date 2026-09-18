#include "light.h"

// NOTE(trist007):  light is inside the screen at z = 1;
light_t light = {
.direction = { 0, 0, 1 }
    // .x = 0,
    // .y = 0,
    // .z = 1
};

uint32_t light_apply_intensity(uint32_t original_color, float percentage_factor)
{
  // NOTE(trist007): & bitwise operation only affects the FF part, all the 0s are masked
  uint32_t a = (original_color & 0xFF000000);
  uint32_t r = (original_color & 0x00FF0000) * percentage_factor;
  uint32_t g = (original_color & 0x0000FF00) * percentage_factor;
  uint32_t b = (original_color & 0x000000FF) * percentage_factor;

  uint32_t new_color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);

  return new_color;
}
