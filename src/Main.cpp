#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

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
    std::string name;
    glm::vec3 value;

    while (!sair)
    {
      std::getline(std::cin, entrada);
      std::stringstream ss(entrada);
      ss >> comando;

      if (comando == "add_shape")
      {
        std::string shape;
        ss >> shape >> name;
        scene.AddObject(shape, name);
      }
      else if (comando == "remove_shape")
      {
        ss >> name;
        scene.RemoveObject(name);
      }
      else if (comando == "color")
      {
        ss >> name >> value.x >> value.y >> value.z;
        scene.ChangeObjectColor(name, value);
      }
      else if (comando == "translate")
      {
        ss >> name >> value.x >> value.y >> value.z;
        scene.TranslateObject(name, value);
      }
      else if (comando == "scale")
      {
        ss >> name >> value.x >> value.y >> value.z;
        scene.ScaleObject(name, value);
      }
      else if (comando == "rotate")
      {
        float angle;
        ss >> name >> angle >> value.x >> value.y >> value.z;
        scene.RotateObject(name, angle, value);
      }
      else if (comando == "axis_on")
      {
        scene.SetAxis(true);
      }
      else if (comando == "axis_off")
      {
        scene.SetAxis(false);
      }
      else if (comando == "wire_on")
      {
        scene.SetWire(true);
      }
      else if (comando == "wire_off")
      {
        scene.SetWire(false);
      }
      else if (comando == "quit")
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
