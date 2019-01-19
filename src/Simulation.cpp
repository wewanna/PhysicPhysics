//
// Created by Cheolwan Park on 19/01/2019.
//

#include "Simulation.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <imgui.h>

namespace PhysicPhysics {
Simulation::Simulation()
:m_particle_size(0.01f), m_scale(2.0f), m_projection(),
m_simulation_box() {
  ;
}

void Simulation::update() {
  m_simulation_box.update();

  float scale_x = m_scale/2.0f;
  float scale_y = 3.0f*scale_x/4.0f;
  m_projection = glm::ortho(-scale_x, scale_x, -scale_y, scale_y, 0.1f, 5.0f);
}

void Simulation::render() {
  m_simulation_box.render();
}

void Simulation::render_gui() {
  m_simulation_box.render_gui();

  ImGui::Begin("Simulation");
  ImGui::Text("Particle Simulation Program");
  ImGui::Text("Proving PV=NkT");
  ImGui::SliderFloat("particle size", &m_particle_size, 0.01f, 0.1f);
  ImGui::SliderFloat("scale", &m_scale, 2.0f, 10.0f);
  ImGui::End();
}

const glm::mat4 &Simulation::getProjection() const {
  return m_projection;
}

float Simulation::getParticleSize() const {
  return m_particle_size;
}

Simulation &Simulation::Get() {
  static Simulation instance;
  return instance;
}
}