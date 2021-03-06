//
// Created by Cheolwan Park on 19/01/2019.
//

#include "SimulationBox.h"
#include "Rendering.h"
#include <imgui.h>

namespace PhysicPhysics {

glm::vec2 vertices[] = {
    {0.5f, 0.5f},
    {0.5f, -0.5f},
    {-0.5f, -0.5f},
    {-0.5f, 0.5f}
};

SimulationBox::SimulationBox()
:m_size(1.0f, 1.0f), m_force_sum(0.0f),
m_vao(0), m_vbo(0) {

  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

SimulationBox::~SimulationBox() {
  glDeleteBuffers(1, &m_vbo);
  glDeleteVertexArrays(1, &m_vao);
}

void SimulationBox::update() {
  m_force_sum = 0.0f;

  // update vbo
  constexpr GLbitfield map_buffer_flag = GL_MAP_WRITE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  auto *v = (glm::vec2*) glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertices), map_buffer_flag);
  for(int i=0; i<4; ++i) {
    v[i].x = vertices[i].x * m_size.x;
    v[i].y = vertices[i].y * m_size.y;
  }
  glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertices));
  glUnmapBuffer(GL_ARRAY_BUFFER);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SimulationBox::render() {
  glBindVertexArray(m_vao);
  glDrawArrays(GL_LINE_LOOP, 0, 4);
  glBindVertexArray(0);
}

void SimulationBox::render_gui() {
  ImGui::Begin("SimulationBox");
  ImGui::SliderFloat("width", &m_size.x, 0.5f, 2.0f);
  ImGui::SliderFloat("height", &m_size.y, 0.5f, 2.0f);
  ImGui::Text("P : %.4f (N/m)\n", getPressure());
  ImGui::Text("S : %.4f (m^2)\n", getSurface());
  ImGui::End();
}

void SimulationBox::reset(glm::vec2 size) {
  m_size = size;
  m_force_sum = 0.0f;
}

void SimulationBox::force(float force) {
  m_force_sum += force;
}

void SimulationBox::resize(glm::vec2 size) {
  m_size = size;
}

int SimulationBox::isIncludingPoint(glm::vec2 p) const {
  glm::vec2 half_size = m_size/2.0f;
  if(p.y > half_size.y)
    return 1;
  else if(p.x < -half_size.x)
    return 2;
  else if(p.y < -half_size.y)
    return 3;
  else if(p.x > half_size.x)
    return 4;
  else
    return 0;
}

float SimulationBox::getPressure() const {
  return m_force_sum/(2*(m_size.x+m_size.y));
}

const glm::vec2 &SimulationBox::getSize() const {
  return m_size;
}

float SimulationBox::getSurface() const {
  return m_size.x*m_size.y;
}






}