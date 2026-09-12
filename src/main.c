#include "display.h"
#include "vector.h"
#include "array.h"
#include "mesh.h"

// ! NOTE: trist007: coordinate system handedness
// ! left handedness the Z goes positive farther away
// ! right handedness the Z goes negative farther away

///////////////////////////////////////////////////////////////////////
// Declare an array of vectors / points
///////////////////////////////////////////////////////////////////////

triangle_t* triangles_to_render = NULL;

// NOTE(trist007): using world space origin for the camera
vec3_t camera_position = { 0, 0, 0 };
float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;

mesh_t mesh;

void
setup(void)
{
  // Allocating the required memory in bytes to hold the color buffer
  color_buffer = (u32*)malloc(sizeof(u32) * window_width * window_height);

  // creating SDL texture that is used to display color buffer
  color_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height
  );
    
  // Loads the cube values in the mesh data structure
  // load_cube_mesh_data();
  load_file_mesh_data("assets/cube.obj");
}

void
process_input(void)
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
    case SDL_QUIT:
      is_running = false;
      break;

    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
        is_running = false;
      break;
  }
}

///////////////////////////////////////////////////////////////////////
// Function that receives a 3D vector and returns a projected 2D point
///////////////////////////////////////////////////////////////////////
vec2_t
project(vec3_t point)
{
  vec2_t projected_point = {
  // ! NOTE: trist007: this is known as perspective divide
  // ! we divide by Z to give the illusion of depth
  // ! without this we have an orthographic projection instead
  // ! of a perspective projection
  .x = (fov_factor * point.x) / point.z,
  .y = (fov_factor * point.y) / point.z,
  };

  return(projected_point);

}

void
update(void)
{
  // ! NOTE: trist007: waits until FRAME_TARGET_TIME have been reached
  // ! it's previous_frame_time + FRAME_TARGET_TIME because you need a timestamp
  // ! as to when to start FRAME_TARGET_TIME and that checkpoint gets set at the top
  // ! of update
  // while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));

  // if (previous_frame_time < previous_frame_time + FRAME_TARGET_TIME)

  while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));
    
  previous_frame_time = SDL_GetTicks(); // in milliseconds

  // Initialize the array of triangles to render
  triangles_to_render = NULL;
    
  mesh.rotation.x += 0.01;
  mesh.rotation.y += 0.01;
  mesh.rotation.z += 0.02;

  // Loop all triangle faces of our mesh
  int num_faces = array_length(mesh.faces);
  for (int i = 0; i < num_faces; i++) {
    face_t mesh_face = mesh.faces[i];

    vec3_t face_vertices[3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    vec3_t transformed_vertices[3];

    // Loop all three vertices of this current face and apply transformations
    for (int j = 0; j < 3; j++) {
      vec3_t transformed_vertex = face_vertices[j];

      transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
      transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
      transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

      // Translate the vertex away from the camera
      transformed_vertex.z += 5;

      // Save transformed vertex in the array of transformed vertices
      transformed_vertices[j] = transformed_vertex;
    }

    vec3_t vector_a = transformed_vertices[0]; /*    A    */
    vec3_t vector_b = transformed_vertices[1]; /*   / \   */ // Clockwise to normal is away 
    vec3_t vector_c = transformed_vertices[2]; /*  C---B  */

    // Get the vector subtraction of B-A and C-A
    vec3_t vector_ab = vec3_subtract(vector_b, vector_a);
    vec3_t vector_ac = vec3_subtract(vector_c, vector_a);

    vec3_normalize(&vector_ab);
    vec3_normalize(&vector_ac);

    // NOTE(trist007): We are using a LHS Left-Handed System where Z+ as
    // it goes away from camera so do ClockWise hence vec3_cross(vector_ab, vector_ac)
    // Get Dot Product to find Normal N
    // Order of parameters are VERY important use Clockwise for LHS and CCW for RHS
    vec3_t normal = vec3_cross(vector_ab, vector_ac);

    // Normalize the face normal vector
    vec3_normalize(&normal);

    // Find the vector between a point in the triangle and the camera origin
    vec3_t camera_ray = vec3_subtract(camera_position, vector_a);

    // Calculate how aligned is my camera_ray with the face normal (using dot product)
    // Do not have to worry about order of the parameters since a x b = b x a
    float dot_normal_camera = vec3_dot(normal, camera_ray);

    // If true then next iteration, bypasing this one or CULLING these faces
    // Bypass the triangles that are looking away from the camera
    if (dot_normal_camera < 0) continue;

    triangle_t projected_triangle;
    // Loop all three vertices to perform projection
    for (int k = 0; k < 3; k++)
    {
      // Project the current vertex
      vec2_t projected_point = project(transformed_vertices[k]);

      // Scale and translate the projected points to the middle of the screen
      projected_point.x += (window_width / 2);
      projected_point.y += (window_height / 2);

      projected_triangle.points[k] = projected_point;
    }

    // Save the projected triangle in the array of triangles to render
    // triangles_to_render[i] = projected_triangle;
    array_push(triangles_to_render, projected_triangle);
  }
}

void
render(void)
{
  draw_grid();

  // Loop all projected triangles and render them
  int num_triangles = array_length(triangles_to_render);
  for (int i = 0; i < num_triangles; i++)
  {
    // Draw vertex points
    triangle_t triangle = triangles_to_render[i];

    // Draw triangle
    draw_triangle(triangle.points[0].x, triangle.points[0].y,
                  triangle.points[1].x, triangle.points[1].y,
                  triangle.points[2].x, triangle.points[2].y);
  }

  // Clear the array of tris to render every frame
  array_free(triangles_to_render);

  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

void
free_resources(void)
{
  free(color_buffer);
  array_free(mesh.vertices);
  array_free(mesh.faces);
}

int
main (int argc, char *argv[])
{
  is_running = initialize_window();
    
  setup();

  while (is_running)
  {
    process_input();
    update();
    render();
  }

  destroy_window();
  free_resources();

	return(0);
}
