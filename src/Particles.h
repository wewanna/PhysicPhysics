//
// Created by Cheolwan Park on 20/01/2019.
//

#ifndef PHYSICPHYSICS_PARTICLES_H
#define PHYSICPHYSICS_PARTICLES_H

#include "calculation/particle.h"
#include <OpengL/gl3.h>

namespace PhysicPhysics {
class Particles {
 public:
  Particles();

  Particles(const Particles &other) = delete;

  ~Particles();

  Particles &operator=(const Particles &other) = delete;

  void update();

  void render();

  void reset(unsigned int count,  const glm::vec2 &box_size, float temperature);

 private:
  particle *m_particles;
  unsigned int m_count;

  GLuint m_vao;
  GLuint m_vbo;
};
}

#endif //PHYSICPHYSICS_PARTICLES_H
