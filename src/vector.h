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

//////////////////////////////////////////////////////////////
// Vector 2D Functions
//////////////////////////////////////////////////////////////
float  vec2_length(vec2_t v);
vec2_t vec2_add(vec2_t v1, vec2_t v2);
vec2_t vec2_subtract(vec2_t v1, vec2_t v2);
vec2_t vec2_mul(vec2_t v, float factor);
vec2_t vec2_div(vec2_t v, float factor);
float  vec2_dot(vec2_t a, vec2_t b);
void   vec2_normalize(vec2_t* v);


//////////////////////////////////////////////////////////////
// Vector 3D Functions
//////////////////////////////////////////////////////////////
float  vec3_length(vec3_t v);
vec3_t vec3_add(vec3_t v1, vec3_t v2);
vec3_t vec3_subtract(vec3_t v1, vec3_t v2);
vec3_t vec3_mul(vec3_t v, float factor);
vec3_t vec3_div(vec3_t v, float factor);
vec3_t vec3_cross(vec3_t a, vec3_t b);
float  vec3_dot(vec3_t a, vec3_t b);
void   vec3_normalize(vec3_t* v);

#endif // VECTOR_H
