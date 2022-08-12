#include <iostream>

using namespace std;

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
#include <iostream>

const float sector = 135.5;
const int dist = 2;

class Unit {
 public:
  Unit(string id, glm::vec2 position, glm::vec2 direction)
      : id_(id), position_(position), direction_(direction) {}
  string id() const {
    return id_;
  }
  const glm::vec2& position() const {
    return position_;
  }
  const glm::vec2& direction() const {
    return direction_;
  }

 private:
  string id_;
  glm::vec2 position_;
  glm::vec2 direction_;
};


//bool areClockwise(v1, v2) {
//  return -v1.x*v2.y + v1.y*v2.x > 0;
//}


std::pair<glm::vec2, glm::vec2>  sectorBounds(glm::vec2 direction, float angle) {
  float angleDiv2 = angle/2.0;
  auto sectorStart = glm::rotate(direction, glm::radians(-angleDiv2));
  auto sectorEnd = glm::rotate(direction, glm::radians(angleDiv2));
  return make_pair(sectorStart, sectorEnd);
}

bool isInsideSector() {

  return true;
}

bool isSeeUnit(Unit seesUnit, Unit unit) {
  auto bounds = sectorBounds(seesUnit.direction(), sector);

  cout << seesUnit.direction().x << " " << seesUnit.direction().y << endl;
  cout << bounds.first.x << " " << bounds.first.y << " " << bounds.second.x << " " << bounds.second.y << endl;
  isInsideSector();
}



int main() {
  cout << "Hello World!" << endl;




  vector<Unit> units;
  units.emplace_back(Unit{"1", glm::vec2{1.f, 1.f}, glm::vec2{0.f, 1.f}});
  units.emplace_back(Unit{"2", glm::vec2{1.f, 2.f}, glm::vec2{1.f, 0.f}});




  for (const auto& seesUnit : units) {

    for (const auto& unit : units) {
      if (seesUnit.id() != unit.id()) {
        isSeeUnit(seesUnit, unit);
      }
    }
  }

  return 0;
}
