#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "particle.h"

using namespace glm;

particle :: particle()
{
    x = 1.0;
    y = 1.0;
    radius = 1.0;
    mass = 1.0;
    velocity = 1.0;
    direction = vec2(1,1);
}

particle :: particle(double xpos, double ypos, double r, double m, double v, vec2 d)
{
    x = xpos;
    y = ypos;
    radius = r;
    mass = m;
    velocity = v;
    direction = d;
}

void particle :: moving() {
    x += velocity * direction.x;
    y += velocity * direction.y;
}

void particle :: breakingwall(int wall) {
    vec2 walldirection;

    switch (wall) {
        case 1:
        case 3:
            walldirection = vec2(1,0);
        case 2:
        case 4:
            walldirection = vec2(0,1);
    }

}

void particle :: breaking(particle target)
{
    x = 2;
}