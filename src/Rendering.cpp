#include "Rendering.h"
#include "Simulation.h"
#include <stdio.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint shader_program = 0;
params locations;

// shader sources
const char *vert_source = R"glsl(
#version 410 core
layout(location = 0) in vec2 position;
uniform mat4 vp;
uniform float psize;
void main() {
  gl_Position = vp * vec4(position, 0.0, 1.0);
  gl_PointSize = psize;
}
  )glsl";

const char *frag_source = R"glsl(
#version 410 core
out vec4 out_color;
void main() {
  out_color = vec4(1.0, 1.0, 1.0, 1.0);
}
  )glsl";

int init_shader() {
  // compile shader
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vertex_shader, 1, &vert_source, 0);
  glShaderSource(fragment_shader, 1, &frag_source, 0);

  GLint status = 0;

  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
  if(GL_TRUE != status) {
    char buf[512] = {0,};
    glGetShaderInfoLog(vertex_shader, 512, 0, buf);
    fprintf(stderr, "failed compiling vertex shader :\n%511s\n", buf);
    return false;
  }

  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
  if(GL_TRUE != status) {
    char buf[512] = {0,};
    glGetShaderInfoLog(fragment_shader, 512, 0, buf);
    fprintf(stderr, "failed compiling fragment shader :\n%511s\n", buf);
    return false;
  }

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glBindFragDataLocation(shader_program, 0, "out_color");
  glLinkProgram(shader_program);
  glUseProgram(shader_program);

  // link params
  locations.vp = glGetUniformLocation(shader_program, "vp");
  locations.particle_size = glGetUniformLocation(shader_program, "psize");
  glUseProgram(0);

  return true;
}

void render() {
  glUseProgram(shader_program);

  PhysicPhysics::Simulation &simulation = PhysicPhysics::Simulation::Get();

  glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 vp = simulation.getProjection() * view;

  glUniformMatrix4fv(locations.vp,
                     1, GL_FALSE,
                     glm::value_ptr(vp));
  glUniform1f(locations.particle_size, simulation.getParticleSize());

  simulation.render();

  glUseProgram(0);
}