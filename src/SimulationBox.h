//
// Created by Cheolwan Park on 19/01/2019.
//

#ifndef PHYSICPHYSICS_BOX_H
#define PHYSICPHYSICS_BOX_H

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

namespace PhysicPhysics {

class Simulator;

class SimulationBox {
 public:
  SimulationBox();

  SimulationBox(const SimulationBox &other) = default;

  ~SimulationBox();

  SimulationBox &operator=(const SimulationBox &other) = default;

  void update();

  void render();

  void render_gui();

  void reset(glm::vec2 size);

  void force(float force);

  void resize(glm::vec2 size);

  int isIncludingPoint(glm::vec2 p)const;

  float getPressure()const;

  const glm::vec2 &getSize() const;

 private:
  glm::vec2 m_size;
  float m_force_sum;

  GLuint m_vao;
  GLuint m_vbo;
};
}

#endif //PHYSICPHYSICS_BOX_H
