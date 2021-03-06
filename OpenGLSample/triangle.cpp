#include "triangle.h"

#include <iostream>
#include "glad/include/glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

Triangle::Triangle() {}

void Triangle::init() {
  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // link shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      50.0f,  50.0f,  0.0f,  // top right
      50.0f,  -50.0f, 0.0f,  // bottom right
      -50.0f, -50.0f, 0.0f,  // bottom left
      -50.0f, 50.0f,  0.0f   // top left
  };

  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3,  // first Triangle
      1, 2, 3   // second Triangle
  };

  glGenVertexArrays(1, &VAO);
  glGenVertexArrays(1, &VAO2);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
//VAO start
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

//VAO2 start
  glBindVertexArray(VAO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Triangle::render(glm::mat4 projectionMatrix) {


  // draw our first triangle
  int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  int transformLoc = glGetUniformLocation(shaderProgram, "transform");


  glUseProgram(shaderProgram);
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix * modelViewMatrix_));


  //VAO
  glUniform4f(vertexColorLocation, 0.0f, 0.0, 1.0f, 1.0f);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  //VAO2 
  glUniform4f(vertexColorLocation, 0.0f, 0.3, 0.0f, 1.0f);

 glBindVertexArray(VAO2);  // no need to unbind it every time
 glLineWidth(3.0);
 glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void Triangle::translate(float x, float y) {
  modelViewMatrix_ = glm::translate(modelViewMatrix_, glm::vec3(x, y, 0.0f));
}

void Triangle::rotate(float angle, int x, int y, int z) {
  modelViewMatrix_ = glm::rotate(modelViewMatrix_, glm::radians(angle), glm::vec3(x, y, z));
}
