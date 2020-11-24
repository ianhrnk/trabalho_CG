#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "Model.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

int main(void)
{
  GLFWwindow* window;
  bool sair = false;
  std::string entrada, comando;

  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 640, "Trabalho", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  //=== Incluir funções de callback aqui ===//

  if(glewInit() != GLEW_OK)
    std::cout << "Error!" << std::endl;

  /* Init section */
  glm::mat4 identity_matrix(1.0f);
  glm::mat4 model_matrix(1.0f);
  model_matrix = glm::rotate(model_matrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 projection_matrix = glm::ortho(-2.f, 2.f, -2.f, 2.f, 2.f, -2.f);

  // Shader
  Shader shader("shader/main.vs", "shader/main.fs");
  shader.Bind();

  // Init matrices (Uniforms)
  shader.SetUniformMatrix4fv("model", model_matrix);
  shader.SetUniformMatrix4fv("view", identity_matrix);
  shader.SetUniformMatrix4fv("projection", projection_matrix);
  shader.SetUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); //White

  shader.Unbind();

  Scene scene;
  Renderer renderer(&shader, &scene);

  /* Loop until the user closes the window - Render section */
  while (!glfwWindowShouldClose(window))
  {
    while (!sair)
    {
      std::getline(std::cin, entrada);
      std::stringstream ss(entrada);
      ss >> comando;

      if (comando.compare("add_shape") == 0)
      {
        std::string shape, name;
        ss >> shape >> name;

        if (!scene.SearchModel(name))
          scene.AddModel(shape, name);
      }
      else if (comando.compare("quit") == 0)
      {
        sair = true;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }

      renderer.Draw();
      glfwSwapBuffers(window);
      glfwWaitEvents();
    }
  }

  //render.Finalize();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
