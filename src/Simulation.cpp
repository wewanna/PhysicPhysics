//
// Created by Cheolwan Park on 19/01/2019.
//

#include "Simulation.h"

#include <thread>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <imgui.h>

namespace PhysicPhysics {
Simulation::Simulation()
:m_environment({4, 2.0f, 1.0f, 1.0f, 100}), m_time(), m_projection(),
m_simulation_box(), m_particles() {
  m_time.now = m_time.start = std::chrono::system_clock::now();
  m_particles.reset(m_environment.particle_count,
      m_simulation_box.getSize(), m_environment.temperature);
}

void Simulation::update() {
  // update time
  using std::chrono::duration_cast;
  using std::this_thread::sleep_for;
  time_point last = m_time.now;
  m_time.now = std::chrono::system_clock::now();
  m_time.deltatime = duration_cast<milliseconds>(m_time.now - last);
  if(m_time.deltatime < IDEAL_DELTATIME) {
    sleep_for(IDEAL_DELTATIME - m_time.deltatime);
    m_time.now = std::chrono::system_clock::now();
    m_time.deltatime = duration_cast<milliseconds>(m_time.now - last);
  }

  // update simulating objects
  m_simulation_box.update();
  m_particles.update();

  // update projection matrix
  float scale_x = m_environment.scale/2.0f;
  float scale_y = 3.0f*scale_x/4.0f;
  m_projection = glm::ortho(-scale_x, scale_x, -scale_y, scale_y, 0.1f, 5.0f);
}

void Simulation::render() {
  m_simulation_box.render();
  m_particles.render();
}

void Simulation::render_gui() {
  m_simulation_box.render_gui();

  ImGui::Begin("Simulation");
  ImGui::Text("Particle Simulation Program");
  ImGui::Text("Proving PV=NkT (PS=NkT, P=F/L)");
  ImGui::SliderInt("psize", &m_environment.particle_size, 4, 10);
  ImGui::SliderFloat("scale", &m_environment.scale, 2.0f, 4.0f);
  ImGui::SliderFloat("TimeScale", &m_environment.timescale, 0.1f, 2.0f);
  ImGui::SliderInt("pcount", &m_environment.particle_count, 100, 4096);
  ImGui::SliderFloat("pradius", &particle::radius, 0.01f, 0.1f);
  ImGui::SliderFloat("T", &m_environment.temperature, 1.0f, 373.0f);
  if(ImGui::Button("Reset"))
    reset();
  ImGui::Text("fps : %d", (int)(1000/m_time.deltatime.count()));
  ImGui::Text("Simulating Time : %.2f", getSimulatingTime());

  ImGui::End();
}

void Simulation::reset() {
  m_particles.reset(m_environment.particle_count,
      m_simulation_box.getSize(),
      m_environment.temperature);
}

const glm::mat4 &Simulation::getProjection() const {
  return m_projection;
}

float Simulation::getParticleSize() const {
  return m_environment.particle_size;
}

float Simulation::getDeltaTime() const {
  return (m_time.deltatime.count()/1000.0f)*m_environment.timescale;
}

float Simulation::getSimulatingTime() const {
  using std::chrono::duration_cast;
  milliseconds t = duration_cast<milliseconds>(m_time.now - m_time.start);
  return (t.count()/1000.0f);
}

SimulationBox &Simulation::getSimulationBox() {
  return m_simulation_box;
}

Simulation &Simulation::Get() {
  static Simulation instance;
  return instance;
}
}