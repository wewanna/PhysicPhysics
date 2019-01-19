//
// Created by Cheolwan Park on 19/01/2019.
//

#ifndef PHYSICPHYSICS_SIMULATION_H
#define PHYSICPHYSICS_SIMULATION_H

#include "SimulationBox.h"

#include <chrono>
#include <glm/glm.hpp>

namespace PhysicPhysics {
typedef std::chrono::duration<uint32_t, std::milli> milliseconds;
typedef std::chrono::system_clock::time_point time_point;
constexpr milliseconds IDEAL_DELTATIME(33);

class Time {
 public:
  Time();

  Time(const Time &other) = default;

  ~Time() = default;
};
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

  float getDeltaTime() const;

  float getSimulatingTime() const;

 public:
  static Simulation &Get();

 private:
  struct {
    float particle_size;
    float scale;
    float timescale;
  } m_environment;
  struct {
    time_point now;
    time_point start;
    milliseconds deltatime;
  } m_time;
  glm::mat4 m_projection;
  SimulationBox m_simulation_box;
};
}

#endif //PHYSICPHYSICS_SIMULATION_H
