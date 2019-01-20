#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective


using namespace glm;

class particle {
public :
    float x;
    float y;
    float radius;
    float mass;
    double velocity;
    vec2 direction;
    particle ();
    particle (double x, double y);
    particle (double x, double y, double r, double mass, vec2 d);
    void breakingwall(int wall);
    void moving();
    void breaking(particle target);
};