#ifndef MESH_H
#define MESH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "vector.h"
#include "triangle.h"
#include "array.h"

//////////////////////////////////////////////////////////////////////
// Define a struct for dynamic size meshes with array of vertices and faces
////////////////////////////////////////////////////////////////////// 
typedef struct mesh_t mesh_t;
struct mesh_t {
  vec3_t* vertices; // dynamic array of vertices
  face_t* faces;    // dynamic array of faces
  vec3_t rotation;  // rotation with x, y, and z values
};

extern mesh_t mesh;

void load_cube_mesh_data();
void load_file_mesh_data(const char* filepath);
void parse_obj(char* data);
void vectorLine(char *ptr);
void faceLine(char *ptr);

#endif // MESH_H
