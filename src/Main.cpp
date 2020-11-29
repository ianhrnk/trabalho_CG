#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "Renderer.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

int main(void)
{
  GLFWwindow* window;

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
  Scene scene;
  Renderer renderer(&scene);

  /* Loop until the user closes the window - Render section */
  while (!glfwWindowShouldClose(window))
  {
    bool sair = false;
    std::string entrada, comando;
    std::string name, type;
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
      else if (comando == "add_light")
      {
        ss >> name >> value.x >> value.y >> value.z;
        scene.AddLight(name, value);
      }
      else if (comando == "remove_light")
      {
        ss >> name;
        scene.RemoveLight(name);
      }
      else if (comando == "reflection_on")
      {
        float k;
        ss >> type >> k;

        renderer.SetReflection(type, k);
      }
      else if (comando == "reflection_off")
      {
        ss >> type;
        renderer.SetReflection(type, 0.0f);
      }
      else if (comando == "shading")
      {
        ss >> type;
        renderer.SetShading(type);
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
      else if (comando == "shear")
      {
        float v0, v1, v2, v3, v4, v5;
        ss >> name >> v0 >> v1 >> v2 >> v3 >> v4 >> v5;
        scene.ShearObject(name, v0, v1, v2, v3, v4, v5);
      }
      else if (comando == "rotate")
      {
        float angle;
        ss >> name >> angle >> value.x >> value.y >> value.z;
        scene.RotateObject(name, angle, value);
      }
      else if (comando == "lookat")
      {
        ss >> value.x >> value.y >> value.z;
        scene.SetCameraLookAt(value);
      }
      else if (comando == "cam")
      {
        ss >> value.x >> value.y >> value.z;
        scene.SetCameraPosition(value);
      }
      else if (comando == "axis_on")
      {
        renderer.SetAxis(true);
      }
      else if (comando == "axis_off")
      {
        renderer.SetAxis(false);
      }
      else if (comando == "lights_on")
      {
        renderer.SetLights(true);
      }
      else if (comando == "lights_off")
      {
        renderer.SetLights(false);
      }
      else if (comando == "wire_on")
      {
        renderer.SetWire(true);
      }
      else if (comando == "wire_off")
      {
        renderer.SetWire(false);
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
