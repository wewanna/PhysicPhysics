#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective


using namespace glm;

class particle {
private :
    int radius;
    int mass;
    double velocity;
    vec2 direction;
public :
    particle ();
    particle (int r, int mass, double v, vec2 direction);
    vec2 breaking(particle target);
};