

#include <future>
#include <GLFW/glfw3.h>

#include "csv.h"
#include "IsSeeUnit.hpp"


//#define RUN_TESTS
constexpr int kMaxThreadCount = 20;

std::pair<bool, bool> testIsSees(const Unit& u1, const Unit& u2) {
  return make_pair(isSeeUnit(u1, u2), isSeeUnit(u2, u1));
}

// isSeesWorker
auto compareUnitWithOtherUnits(const Unit seesUnit, const vector<Unit>& units) {
  string res;
  for (const auto unit : units) {
    if (seesUnit.id() != unit.id()) {
      string seesStr;
      if (isSeeUnit(seesUnit, unit))
        seesStr = " sees ";
      else
        seesStr = " not sees ";

      string resStr =
          "Unit " + seesUnit.id() + seesStr + "Unit " + unit.id() + "\n";

      res.append(resStr);
    }
  }

  return res;
}

void compareAllUnits(const vector<Unit>& units) {

  vector<future<string>> results;
  results.reserve(kMaxThreadCount);
  for (auto it = units.begin(); it != units.end(); it++) {
    results.emplace_back(
        std::async(std::launch::async, compareUnitWithOtherUnits, *it, std::ref(units)));
    // get results
    if (results.size() == kMaxThreadCount or (it + 1) == units.end()) {
      for (auto& res : results) {
        cout << res.get() << endl;
      }
      results.clear();
      results.reserve(kMaxThreadCount);
    }
  }

}

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
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

  // test 10000
  {
    vector<Unit> units;
    for (int i = 0; i < 10000; i++) {
      units.emplace_back(
          Unit{std::to_string(i), glm::vec2{1, 1}, glm::vec2{1, 1}});
    }

    compareAllUnits(units);
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


  compareAllUnits(units);



  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfwSetErrorCallback(error_callback);
  // glfw window creation
  // --------------------
  GLFWwindow* window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 // glfwSetKeyCallback(window, key_callback);

 // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
  //  std::cout << "Failed to initialize GLAD" << std::endl;
  //  return -1;
 // }

//  Triangle t1;
//  t1.init();
//  t1.translate(100, 100);

//  Triangle t2;
//  t2.init();
//  t2.translate(400, 400);
//  t2.rotate(60.0, 1.0, 0.0, 0.0);

  glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    // std::cout << "gfgggggg" << std::endl;
    /* Render here */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    glm::mat4 projectionMatrix = glm::mat4(1.0);
    projectionMatrix = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, -100.0f, 100.0f);

    std::cout << "Failed to create GLFW window" << " x " << cameraPos.x << " y " << cameraPos.y   << " z " << cameraPos.z << std::endl;
    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


   // t1.render(projectionMatrix * viewMatrix);
   // t2.render(projectionMatrix * viewMatrix);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();



  return 0;
}
