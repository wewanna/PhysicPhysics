#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective


using namespace glm;

namespace PhysicPhysics {
class particle {
 public:
  static float radius;
  static float mass;
 public :
  vec2 position;
  vec2 direction;
  particle();
  particle(vec2 &p);
  particle(vec2 &p, vec2 &d);
  void breakingwall(int wall);
  void moving(float deltatime);
  void breaking(particle &target);
};
}