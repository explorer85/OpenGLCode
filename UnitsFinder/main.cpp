#include "IsSeeUnit.hpp"

#define RUN_TESTS

std::pair<bool, bool> testIsSees(const Unit& u1, const Unit& u2) {
  return make_pair(isSeeUnit(u1, u2), isSeeUnit(u2, u1));
}

int main() {

#ifdef RUN_TESTS
  // test1
  {
    Unit u1{"1", glm::vec2{1.f, 1.f}, glm::vec2{0.f, 1.f}};
    Unit u2{"2", glm::vec2{1.f, 2.f}, glm::vec2{1.f, 0.f}};
    auto res = testIsSees(u1, u2);
    assert(res.first && !res.second);
  }
  // test2
  {
    Unit u1{"1", glm::vec2{1.f, 1.f}, glm::vec2{0.f, 1.f}};
    Unit u2{"2", glm::vec2{1.f, 4.f}, glm::vec2{1.f, 0.f}};
    auto res = testIsSees(u1, u2);
    assert(!res.first && !res.second);
  }

  // test2
  {
    Unit u1{"1", glm::vec2{1.f, 1.f}, glm::vec2{0.f, 1.f}};
    Unit u2{"2", glm::vec2{2.f, 1.f}, glm::vec2{-1.f, 0.f}};
    auto res = testIsSees(u1, u2);
    assert(!res.first && res.second);
  }
#endif

  vector<Unit> units;
  units.emplace_back(Unit{"1", glm::vec2{1.f, 1.f}, glm::vec2{0.f, 1.f}});
  units.emplace_back(Unit{"2", glm::vec2{1.f, 2.f}, glm::vec2{1.f, 0.f}});

  for (const auto& seesUnit : units) {
    for (const auto& unit : units) {
      if (seesUnit.id() != unit.id()) {
        if (isSeeUnit(seesUnit, unit))
          cout << "Unit " << seesUnit.id() << " sees "
               << "Unit " << unit.id() << endl;
      }
    }
  }

  return 0;
}
