#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

typedef uint32_t u32;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern u32 *color_buffer;
extern SDL_Texture *color_buffer_texture;
extern int window_width;
extern int window_height;

bool initialize_window(void);
void draw_grid(void);
void draw_pixel(int x, int y);
void draw_rect(int x, int y, int width, int height, u32 color);
void draw_line(int x0, int y0, int x1, int y1);
void clear_color_buffer(u32 color);
void render_color_buffer(void);
void destroy_window(void);

#endif // DISPLAY_H
