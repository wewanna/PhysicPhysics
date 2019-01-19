//
// Created by Cheolwan Park on 19/01/2019.
//

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

extern GLuint shader_program;
struct params {
  GLint vp;
  GLint particle_size;
};
extern params locations;

int init_shader();

void render();