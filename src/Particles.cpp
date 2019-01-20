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
:m_particles(nullptr), m_count(0), m_calculated_temperature(0.0f),
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

void Particles::update() {
  // check collision
  glm::vec2 delta(0.0f);
  float square_radius = 4*particle::radius*particle::radius;
  Simulation &simulation = Simulation::Get();
  SimulationBox &simulation_box = simulation.getSimulationBox();
  int wall = 0;

  for(unsigned int i=0; i<m_count; ++i)
    m_particles[i].moving(simulation.getDeltaTime());

  float squared_velocity_sum = 0.0f, squared_speed = 0.0f;
  for(unsigned int i=0; i<m_count; ++i) {
    for(unsigned int j=i+1; j<m_count; ++j) {
      delta = m_particles[i].position - m_particles[j].position;
      if ((delta.x * delta.x + delta.y * delta.y) < square_radius) {
        m_particles[i].breaking(m_particles[j]);
        m_particles[j].breaking(m_particles[i]);
      }
    }

    const glm::vec2 &v = m_particles[i].direction;
    wall = simulation_box.isIncludingPoint(m_particles[i].position);
    if(0 != wall) {
      m_particles[i].breakingwall(wall, simulation_box.getSize());
      float force = 0.0f;
      switch(wall) {
        case 1:
        case 3: force = v.y; break;
        case 2:
        case 4: force = v.x; break;
        default: break;
      }
      simulation_box.force(2*abs(force));
    }

    // calculate sum of v^2
    squared_speed = v.x*v.x + v.y*v.y;
    if(!isnan(squared_speed))
      squared_velocity_sum += squared_speed;
  }

  // calculate temperature
  squared_velocity_sum /= (float)m_count;
  m_calculated_temperature = squared_velocity_sum/(3.0f*Simulation::k_b);

  // update vbo
  constexpr GLbitfield map_buffer_flag = GL_MAP_WRITE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  auto *v = (glm::vec2*) glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2)*m_count, map_buffer_flag);
  for(unsigned int i=0; i<m_count; ++i) {
    v[i] = m_particles[i].position;
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
  glm::vec2 position(0.0f), velocity(0.0f);
  float theta = 0.0f, distance = 0.0f, particle_velocity = sqrtf(3*Simulation::k_b*temperature);

  for(unsigned int i=0; i<m_count; ++i) {
    theta = 6.28f*((float)range(rnd)/1048576);
    distance = 0.8f*box_size.x*((float)range(rnd)/1048576)/2.0f;
    position.x = cosf(theta); position.y = sinf(theta);
    position *= distance;

    theta = 6.28f*((float)range(rnd)/1048576);
    velocity.x = cosf(theta); velocity.y = sinf(theta);
    velocity *= particle_velocity;

    new (m_particles + i) particle(position, velocity);
  }

  // resize vbo
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*m_count, 0, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

}

float Particles::getCalculatedTemperature() const {
  return m_calculated_temperature;
}

unsigned int Particles::getCount() const {
  return m_count;
}


}