#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective


using namespace glm;

namespace PhysicPhysics {
class particle {
 public:
  static float radius; // 입자 크기
 public :
  vec2 position; // 위치 (x, y)
  vec2 direction; // 방향과 속도 (x방향으로의 속도, y방향으로의 속도)
  particle(); //생성자
  particle(vec2 &p);
  particle(vec2 &p, vec2 &d);
  void breakingwall(int wall, const vec2 &size); // 벽에 부딪혔을 때 발생하는 메소드
  void moving(float deltatime); // 입자가 이동하는 메소드
  void breaking(particle &target); // 입자끼리 부딪혓을 때 발생하는 메소드
};
}