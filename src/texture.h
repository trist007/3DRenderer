#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

typedef struct tex2_t tex2_t;
struct tex2_t
{
  float u;
  float v;
};

extern int texture_width;
extern int texture_height;

extern const uint8_t REDBRICK_TEXTURE[];

extern uint32_t* mesh_texture;

#endif // TEXTURE_H
