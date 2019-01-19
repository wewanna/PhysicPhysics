#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "particle.h"

using namespace glm;

particle :: particle()
{
    radius = 1;
    mass = 1;
    velocity = 1.0;
    direction = vec2(1,1);
}

particle :: particle(int r, int m, double v, vec2 d)
{
    radius = r;
    mass = m;
    velocity = v;
    direction = d;
}

vec2 particle :: breaking(particle target)
{
    
}