#pragma once
#include <glm/glm.hpp>

class Triangle {
 public:
  Triangle();
  void init();
  void render(glm::mat4 projectionMatrix);
  void translate(float x, float y);
  void rotate(float angle, int x, int y, int z);

 private:
  unsigned int shaderProgram;
  unsigned int VBO, VAO, VAO2, EBO;
  glm::mat4 modelViewMatrix_ = glm::mat4(1.0);
};

