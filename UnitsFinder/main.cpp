#include "IsSeeUnit.hpp"

#include <future>
#include "csv.h"

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

  //test 10000
  {
    vector<Unit> units;
    for (int i = 0; i < 10000; i++) {
      units.emplace_back(
          Unit{std::to_string(i), glm::vec2{1, 1}, glm::vec2{1, 1}});
    }

    // worker
    auto isSeesWorker = [](const Unit seesUnit, const vector<Unit>& units) {
       string res;
      for (const auto unit : units) {
         if (seesUnit.id() != unit.id()) {
           string seesStr;
         if (isSeeUnit(seesUnit, unit))
          seesStr = " sees ";
         else
          seesStr = " not sees ";

         string resStr = "Unit " + seesUnit.id() + seesStr + "Unit " + unit.id() + "\n";

         res.append(resStr);
           }
      }

      return res;
    };

    vector<future<string>> futures;
    for (const auto& seesUnit : units) {
      futures.emplace_back(
          std::async(std::launch::async, isSeesWorker, seesUnit, std::ref(units)));
    }

    // result
    cout << "result" << endl;
    for (auto& fut : futures) {
      cout << fut.get() << endl;
    }
  }
  return 0;

#endif

  io::CSVReader<5> in("units.csv");
  in.read_header(io::ignore_extra_column, "id", "px", "py", "vx", "vy");
  std::string id;
  float px, py, dx, dy;

  vector<Unit> units;
  while (in.read_row(id, px, py, dx, dy)) {
    units.emplace_back(Unit{id, glm::vec2{px, py}, glm::vec2{dx, dy}});
  }

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
