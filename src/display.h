#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL.h>

typedef uint32_t u32;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern u32 *color_buffer;
extern SDL_Texture *color_buffer_texture;

extern int window_width;
extern int window_height;

bool initialize_window(void);
void clear_color_buffer(u32 color);
void render_color_buffer(void);
void draw_grid(u32 color);
void draw_rectangle(int x, int y, int width, int height, u32 color);
void destroy_window(void);

#endif // DISPLAY_H