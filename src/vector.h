#ifndef VECTOR_H
#define VECTOR_H

typedef struct vec2_t vec2_t;
struct vec2_t
{
    float x;
    float y;
};

typedef struct vec3_t vec3_t;
struct vec3_t
{
    float x;
    float y;
    float z;
};

typedef struct camera_t camera_t;
struct camera_t
{
    vec3_t position;
    vec3_t rotation;
    float  fov_angle;
};

// ! TODO: trist007: matrices
vec2_t project(vec3_t point);

void transform_points(void);

vec3_t vec3_rotate_x(vec3_t v, float angle);
vec3_t vec3_rotate_y(vec3_t v, float angle);
vec3_t vec3_rotate_z(vec3_t v, float angle);

#endif // VECTOR_H