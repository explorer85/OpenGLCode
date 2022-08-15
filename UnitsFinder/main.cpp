#include "IsSeeUnit.hpp"



int main() {
  //test
//  {
//    Unit u1{"1", glm::vec2{1.f, 1.f}, glm::vec2{0.f, 1.f}};
//    Unit u2{"2", glm::vec2{1.f, 2.f}, glm::vec2{1.f, 0.f}};
//    cout << isSeeUnit(u1, u2) << endl;

//  }




  vector<Unit> units;
  units.emplace_back(Unit{"1", glm::vec2{1.f, 1.f}, glm::vec2{0.f, 1.f}});
  units.emplace_back(Unit{"2", glm::vec2{1.f, 2.f}, glm::vec2{1.f, 0.f}});




  for (const auto& seesUnit : units) {

    for (const auto& unit : units) {
      if (seesUnit.id() != unit.id()) {
        if (isSeeUnit(seesUnit, unit))
          cout << "Unit " << seesUnit.id() << " sees " << "Unit " << unit.id() << endl;
      }
    }
  }

  return 0;
}
