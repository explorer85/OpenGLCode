
#include <iostream>
#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "triangle.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}


glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

      GLfloat cameraSpeed = 4.05f;
      if(key == GLFW_KEY_W) {
    cameraPos -= cameraSpeed * cameraUp;

      }
  if(key == GLFW_KEY_S)
    cameraPos += cameraSpeed * cameraUp;

  //пользуемся свойствами веторного произведения векторов
  //(перемена мест множителей дает другое ноправление нормали)
  if(key == GLFW_KEY_A)
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if(key == GLFW_KEY_D)
    cameraPos += glm::normalize(glm::cross(cameraUp, cameraFront)) * cameraSpeed;
}

int main(void) {

  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 trans = glm::mat4(1.0);
  //trans = glm::translate(trans, glm::vec3(0.1f, 0.1f, 0.0f));
  vec = trans * vec;
  std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;





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
  glfwSetKeyCallback(window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Triangle t1;
  t1.init();
  t1.translate(100, 100);

  Triangle t2;
  t2.init();
  t2.translate(400, 400);
  t2.rotate(60.0, 1.0, 0.0, 0.0);


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


    t1.render(projectionMatrix * viewMatrix);
    t2.render(projectionMatrix * viewMatrix);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
