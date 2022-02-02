#pragma once
#include <glm/glm.hpp>

class Triangle {
 public:
  Triangle();
  void init();
  void render();
  void translate(float x, float y);

 private:
  unsigned int shaderProgram;
  unsigned int VBO, VAO, VAO2, EBO;
  glm::mat4 modelViewMatrix_ = glm::mat4(1.0);
};

