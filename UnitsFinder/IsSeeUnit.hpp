#pragma once

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



std::pair<glm::vec2, glm::vec2>  sectorBounds(glm::vec2 direction, float angle) {
  float angleDiv2 = angle/2.0;
  auto sectorStart = glm::rotate(direction, glm::radians(-angleDiv2));
  auto sectorEnd = glm::rotate(direction, glm::radians(angleDiv2));
  return make_pair(sectorStart, sectorEnd);
}

bool areCounterClockwise(glm::vec2 v1, glm::vec2 v2) {
  glm::vec2 n1 = {-v1.y, v1.x};
  float proj =  v2.x*n1.x + v2.y*n1.y;
  return proj > 0;
}

bool isWithinRadius(glm::vec2 v, float radiusSquared) {
  return v.x*v.x + v.y*v.y <= radiusSquared;
}

bool isInsideSector(glm::vec2 point, glm::vec2 sectorCenter, glm::vec2 sectorStart, glm::vec2 sectorEnd, float radiusSquared) {

  auto relPoint =  point - sectorCenter;

  bool counterClockwiseRelStart = areCounterClockwise(sectorStart, relPoint);
  bool counterClockwiseRelEnd = areCounterClockwise(sectorEnd, relPoint);

  return counterClockwiseRelStart && !counterClockwiseRelEnd && isWithinRadius(relPoint, radiusSquared);

}

bool isSeeUnit(Unit seesUnit, Unit unit) {
  auto bounds = sectorBounds(seesUnit.direction(), sector);

  //cout << seesUnit.direction().x << " " << seesUnit.direction().y << endl;
  //cout << bounds.first.x << " " << bounds.first.y << " " << bounds.second.x << " " << bounds.second.y << endl;
  return isInsideSector(unit.position(), seesUnit.position(), bounds.first, bounds.second, dist * dist);
}


