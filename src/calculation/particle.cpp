#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <cmath>
#include "particle.h"

using namespace glm;

namespace PhysicPhysics {

float particle::radius = 0.05f;
float particle::mass = 1.0f;

particle::particle()
: position(0.0f, 0.0f), direction(0.0f, 0.0f) {
    ;
}

particle::particle(vec2 &p) // 생성자 1
: position(p), direction(0.0f, 0.0f) {
    ;
}

particle::particle(vec2 &p, vec2 &d) // 생성자 2
: position(p), direction(d) {
    ;
}

void particle::moving(float deltatime) { // 랜더러쪽에서 1초마다 파티클 입자에 해당 메소드를 실행시켜야함
    position += direction * deltatime;
}

void particle::breakingwall(int wall, const vec2 &size) { // 벽에 부딫쳤을 때 메소드
    // 윗벽 1, 왼쪽벽 2, 아래벽 3, 오른쪽 벽 4
    switch (wall) {
        case 1:
        case 3:direction.y *= -1; break; // 윗벽, 아래벽에 부딫혔을 때 y 축 방향으로의 속도 반대로 바꿈
        case 2:
        case 4:direction.x *= -1; break; // 왼쪽벽, 오른쪽벽에 부딫혔을 때 x 축 방향으로의 속도 반대로 바꿈
        default: break;
    }
    switch (wall) {
      case 1: position.y = size.y/2.0f; break;
      case 2: position.x = -size.x/2.0f; break;
      case 3: position.y = -size.y/2.0f; break;
      case 4: position.x = size.x/2.0f; break;
      default: break;
    }
}

void particle::breaking(particle &target) {
  glm::vec2 dv = this->position - target.position;

  float betdistance = dv.length();
  float sinTheta = dv.y / betdistance;
  float cosTheta = dv.x / betdistance;

    //충돌 후 x축으로의 속도
    float vxAp =
        (2 * mass) / (mass + mass) * (target.direction.x * cosTheta + target.direction.y * sinTheta);
    //충돌 후 y축으로의 속도
    float vyAp = direction.x * (-sinTheta) + target.direction.y * cosTheta;

    // 두 공이 겹쳐질 때 분리됨
//    float angleAB = atan2(dv.y, dv.x);
//    float angleBA = atan2(-dv.y, -dv.x);
//    float moveToDistance = abs(radius + target.radius) - betdistance;
//    position.x = position.x + moveToDistance * cos(angleAB);

    direction.x = vxAp;
    direction.y = vyAp;

}
}