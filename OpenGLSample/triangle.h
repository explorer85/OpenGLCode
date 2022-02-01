#pragma once

class Triangle {
 public:
  Triangle();
  void init();
  void render();

 private:
  unsigned int shaderProgram;
  unsigned int VBO, VAO, EBO;
};

