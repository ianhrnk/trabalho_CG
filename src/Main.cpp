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
  Shader shader("shader/main.vs", "shader/main.fs");
  shader.InitMatrices();
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

        if (scene.SearchModel(name) == nullptr)
          scene.AddModel(shape, name);
      }
      else if (comando.compare("color") == 0)
      {
        std::string name;
        float v0, v1, v2;
        ss >> name >> v0 >> v1 >> v2;

        Model* model = scene.SearchModel(name);
        if (model != nullptr)
          model->SetColor(v0, v1, v2);
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

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
