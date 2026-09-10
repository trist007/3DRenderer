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
//

triangle_t* triangles_to_render = NULL;

vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
vec3_t cube_rotation = { .x = 0, .y = 0, .z = 0 };

float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;

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
    
  cube_rotation.x += 0.01;
  cube_rotation.y += 0.01;
  cube_rotation.z += 0.01;

  // Loop all triangle faces of our mesh
  for (int i = 0; i < N_MESH_FACES; i++) {
    face_t mesh_face = mesh_faces[i];

    vec3_t face_vertices[3];
    face_vertices[0] = mesh_vertices[mesh_face.a - 1];
    face_vertices[1] = mesh_vertices[mesh_face.b - 1];
    face_vertices[2] = mesh_vertices[mesh_face.c - 1];

    triangle_t projected_triangle;

    // Loop all three vertices of this current face and apply transformations
    for (int j = 0; j < 3; j++) {
      vec3_t transformed_vertex = face_vertices[j];

      transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
      transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
      transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

      // Translate the vertex away from the camera
      transformed_vertex.z -= camera_position.z;

      // Project the current vertex
      vec2_t projected_point = project(transformed_vertex);

      // Scale and translate the projected points to the middle of the screen
      projected_point.x += (window_width / 2);
      projected_point.y += (window_height / 2);

      projected_triangle.points[j] = projected_point;
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
        draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFFFF00);
        draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFFFF00);
        draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFFFF00);

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

	return(0);
}
