#include <math.h>
#include "vector.h"

/////////////////////////////////////////////////////////////////////////
// Implementations of Vector 2D functions
/////////////////////////////////////////////////////////////////////////
float
vec2_length(vec2_t v)
{
  return sqrt((v.x * v.x) + (v.y * v.y));
}

vec2_t
vec2_add(vec2_t v1, vec2_t v2)
{
  vec2_t result = { 0 };

  result.x = v1.x + v2.x;
  result.y = v1.y + v2.y;

  return result;
}

vec2_t
vec2_subtract(vec2_t v1, vec2_t v2)
{
  vec2_t result = { 0 };
  
  result.x = v1.x - v2.x;
  result.y = v1.y - v2.y;

  return result;
}

vec2_t
vec2_mul(vec2_t v, float factor)
{
  vec2_t result = {
    .x = v.x * factor,
    .y = v.y * factor
  };

  return result;
}

vec2_t
vec2_div(vec2_t v, float factor)
{
  vec2_t result = {
    .x = v.x / factor,
    .y = v.y / factor
  };
  return result;
}

float
vec2_dot(vec2_t a, vec2_t b)
{
  // A x B = AxBx + AyBy
  return (a.x * b.x) + (a.y * b.y);
}
/////////////////////////////////////////////////////////////////////////
// Implementations of Vector 3D functions
/////////////////////////////////////////////////////////////////////////
float
vec3_length(vec3_t v)
{
  return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

vec3_t
vec3_add(vec3_t v1, vec3_t v2)
{
  vec3_t result = { 0 };

  result.x = v1.x + v2.x;
  result.y = v1.y + v2.y;
  result.z = v1.z + v2.z;
  
  return result;
}

vec3_t
vec3_subtract(vec3_t v1, vec3_t v2)
{
  vec3_t result = { 0 };

  result.x = v1.x - v2.x;
  result.y = v1.y - v2.y;
  result.z = v1.z - v2.z;
  
  return result;
}

vec3_t
vec3_mul(vec3_t v, float factor)
{
  vec3_t result = {
    .x = v.x * factor,
    .y = v.y * factor,
    .z = v.z * factor
  };

  return result;
}

vec3_t
vec3_div(vec3_t v, float factor)
{
  vec3_t result = {
    .x = v.x / factor,
    .y = v.y / factor,
    .z = v.z / factor
  };
  return result;
}

// NOTE(trist007): the vec3_t that gets returned is the normal
// the normal is Perpendicular to a and b
vec3_t
vec3_cross(vec3_t a, vec3_t b)
{
  // (B - A) x (C - A) = Normal (Perpendicular Vector) 90 degree angle from triangle face
  /* Nx =  AyBz - AzBy */
  /* Ny =  AzBx - AxBz */
  /* Nz =  AxBy - AyBx */

  vec3_t result = {
    .x = (a.y * b.z) - (a.z * b.y),
    .y = (a.z * b.x) - (a.x * b.z),
    .z = (a.x * b.y) - (a.y * b.x)
  };
  
  return result;
}

// NOTE(trist007): finds how aligned the two vectors are from 1.0 to -1.0
// 0.0 if they are Perpendicular to each other
float
vec3_dot(vec3_t a, vec3_t b)
{
  // A x B = AxBx + AyBy
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3_t
vec3_rotate_x(vec3_t v, float angle)
{
    vec3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };
    return(rotated_vector);
}

vec3_t
vec3_rotate_y(vec3_t v, float angle)
{
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };
    return(rotated_vector);
}

vec3_t
vec3_rotate_z(vec3_t v, float angle)
{
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };
    return(rotated_vector);
}
