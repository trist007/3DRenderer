#include "display.h"

SDL_Window *window;
SDL_Renderer *renderer;

u32 *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;

int window_width = 800;
int window_height = 600;

bool
initialize_window(void)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    fprintf(stderr, "Error initializing SDL.\n");
    return(false);
  }

  // Use SDL to query what is the fullscreen max width and height
  SDL_DisplayMode display_mode = { 0 };
  SDL_GetCurrentDisplayMode(0, &display_mode);

  window_width  = display_mode.w;
  window_height = display_mode.h;

  // Create a SDL Window
  window = SDL_CreateWindow(
    NULL,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    window_width,
    window_height,
    SDL_WINDOW_BORDERLESS
  );
  if (!window)
  {
    fprintf(stderr, "Error creating SDL Window.\n");
    return(false);
  }
    
  renderer = SDL_CreateRenderer(window, -1, 0);
    
  if (!renderer)
  {
    fprintf(stderr, "Error creating SDL Renderer.\n");
    return(false);
  }

  // ! NOTE: trist007: if i set createwindow to 800 x 600 then
  // ! this would full screen monitor mode in 800 x 600
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    
  return(true);
}

void
clear_color_buffer(u32 color)
{
  // ! NOTE: trist007: clear every pixel to color
  for (int y = 0; y < window_height; y++)
  {
    for (int x = 0; x < window_width; x++)
    {
      color_buffer[(window_width * y) + x] = color;
    }
  }
}

void
render_color_buffer(void)
{
  SDL_UpdateTexture(
    color_buffer_texture,
    NULL,
    color_buffer,
    (int)(window_width * sizeof(u32))
  );

  SDL_RenderCopy(
    renderer,
    color_buffer_texture,
    NULL,
    NULL
  );
}

void
draw_grid()
{

  u32 color = 0x000000FF;
  
  for (int y = 0; y < window_height; y += 10)
  {
    for (int x = 0; x < window_width; x += 10)
    {
      color_buffer[(window_width * y) + x] = color;
    }
  }
}

void
draw_line(int x0, int y0, int x1, int y1)
{
  int delta_x = (x1 - x0);
  int delta_y = (y1 - y0);

  int side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

  float x_inc = delta_x / (float)side_length;
  float y_inc = delta_y / (float)side_length;

  float current_x = x0;
  float current_y = y0;

  for (int i = 0; i < side_length; i++) {
    draw_pixel(round(current_x), round(current_y));
    current_x += x_inc;
    current_y += y_inc;
  }
}

void
draw_pixel(int x, int y)
{
  u32 color = 0xFFFFFF00;
  // ! NOTE: trist007: make sure x and y are valid coords
  if ( x >= 0 && x < window_width && y >= 0 && y < window_height)
  {
    color_buffer[(window_width * y) + x] = color;
  }
}

void
draw_rect(int x, int y, int width, int height, u32 color)
{
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      int current_x = x + i;
      int current_y = y + j;
      draw_pixel(current_x, current_y);
    }
  }
}

void
destroy_window(void)
{
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
