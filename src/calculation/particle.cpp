#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <cmath>
#include "particle.h"

using namespace glm;

particle :: particle()
{
    x = 1.0; // 현재 X 좌표 위치
    y = 1.0; // 현재 Y 좌표 위치
    radius = 1.0; // 혹시 모르는 반지름
    mass = 1.0; // 질량 (1 고정 입니다)
    direction = vec2(1, 1); // vec2(x 축 방향으로의 속도, y축 방향으로의 속도)
}

particle :: particle(double xpos, double ypos) // 생성자 1
{
    x = xpos;
    y = ypos;
}

particle :: particle(double xpos, double ypos, double r, double m, vec2 d) // 생성자 2
{
    x = xpos;
    y = ypos;
    radius = r;
    mass = m;
    direction = d;
}

void particle :: moving() { // 랜더러쪽에서 1초마다 파티클 입자에 해당 메소드를 실행시켜야함
    x += direction.x; // x 축 방향으로의 속도를 X좌표 위치에 더함
    y += direction.y; // y 축 방향으로의 속도를 Y좌표 위치에 더함
}

void particle :: breakingwall(int wall) { // 벽에 부딫쳤을 때 메소드
    // 윗벽 1, 왼쪽벽 2, 아래벽 3, 오른쪽 벽 4
    switch (wall) {
        case 1:
        case 3:
            direction.y *= -1; // 윗벽, 아래벽에 부딫혔을 때 y 축 방향으로의 속도 반대로 바꿈
        case 2:
        case 4:
            direction.x *= -1; // 왼쪽벽, 오른쪽벽에 부딫혔을 때 x 축 방향으로의 속도 반대로 바꿈
    }
}

void particle :: breaking(particle target)
{
    float dx = x - target.x;
    float dy = y - target.y;

    float betdistance = abs(sqrt(dx*dx + dy*dy));

    float sinTheta = dy / abs(sqrt(dx*dx + dy*dy));
    float cosTheta = dx / abs(sqrt(dx*dx + dy*dy));

    //충돌 후 x축으로의 속도
    float vxAp = (2 * target.mass) / (mass + target.mass)*(target.direction.x*cosTheta + target.direction.y*sinTheta);
    //충돌 후 y축으로의 속도
    float vyAp = direction.x*(-sinTheta) + target.direction.y*cosTheta;

    // 두 공이 겹쳐질 때 분리됨
    float angleAB = atan2(dy,dx);
    float angleBA = atan2(-dy,-dx); 
    float moveToDistance = abs(radius + target.radius) - betdistance;
    x = x + moveToDistance * cos(angleAB);

    direction.x = vxAp;
    direction.y = vyAp;

}