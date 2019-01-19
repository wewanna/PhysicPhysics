//
// Created by Cheolwan Park on 19/01/2019.
//

#ifndef PHYSICPHYSICS_SIMULATION_H
#define PHYSICPHYSICS_SIMULATION_H

#include "SimulationBox.h"

#include <glm/glm.hpp>

namespace PhysicPhysics {
class Simulation {
 private:
  Simulation();

 public:
  Simulation(const Simulation &other) = delete;

  ~Simulation() = default;

  Simulation &operator=(const Simulation &other) = delete;

  void update();

  void render();

  void render_gui();

  const glm::mat4 &getProjection() const;

  float getParticleSize() const;

 public:
  static Simulation &Get();

 private:
  float m_particle_size;
  float m_scale;
  glm::mat4 m_projection;
  SimulationBox m_simulation_box;
};
}

#endif //PHYSICPHYSICS_SIMULATION_H
