//
// Created by Cheolwan Park on 20/01/2019.
//

#include "Particles.h"
#include "Simulation.h"
#include <new>
#include <random>
#include <math.h>

namespace PhysicPhysics {
Particles::Particles()
:m_particles(nullptr), m_count(0),
m_vao(0), m_vbo(0) {
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Particles::~Particles() {
  if(m_particles)
    free(m_particles);
  glDeleteBuffers(1, &m_vbo);
  glDeleteVertexArrays(1, &m_vao);
}

#include <stdio.h>
void Particles::update() {
  // update vbo
  constexpr GLbitfield map_buffer_flag = GL_MAP_WRITE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  auto *v = (glm::vec2*) glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2)*m_count, map_buffer_flag);
  for(unsigned int i=0; i<m_count; ++i) {
    v[i].x = m_particles[i].x;
    v[i].y = m_particles[i].y;
  }
  glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2)*m_count);
  glUnmapBuffer(GL_ARRAY_BUFFER);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Particles::render() {
  glBindVertexArray(m_vao);
  glDrawArrays(GL_POINTS, 0, m_count);
  // glDrawArrays(GL_POINTS, 0, 4);
  glBindVertexArray(0);
}

void Particles::reset(unsigned int count, const glm::vec2 &box_size, float temperature) {
  m_count = count;

  if(m_particles)
    free(m_particles);
  m_particles = (particle*)malloc(sizeof(particle)*m_count);

  std::random_device rd;
  std::mt19937 rnd(rd());
  std::uniform_int_distribution<int> range(0, 1048576);
  float theta = 0.0f, distance = 0.0f;

  for(unsigned int i=0; i<m_count; ++i) {
    theta = 6.28f*((float)range(rnd)/1048576);
    distance = box_size.x*((float)range(rnd)/1048576)/2.0f;
    new (m_particles + i) particle(cosf(theta) * distance, sinf(theta) * distance);
  }

  glm::vec2 dummy[4] = {
      {0.5f, 0.5f},
      {0.5f, -0.5f},
      {-0.5f, -0.5f},
      {-0.5f, 0.5f}
  };

  // resize vbo
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*m_count, 0, GL_DYNAMIC_DRAW);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(dummy), dummy, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

}


}