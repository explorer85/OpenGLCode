#ifndef TRIANGLE_H
#define TRIANGLE_H


class Triangle
{
 public:
  Triangle();
  void render();
 private:
  unsigned int shaderProgram;
  unsigned int VBO, VAO, EBO;
};

#endif // TRIANGLE_H
