#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "Renderer.h"

enum Command {
  add_shape, remove_shape, add_light, remove_light,
  reflection_on, reflection_off, shading,
  translate, scale, shear, rotate, lookat, cam, color,
  save, axis_on, axis_off, lights_on, lights_off,
  wire_on, wire_off, quit
};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

int main(void)
{
  std::map<std::string, Command> str_to_command = {
    {"add_shape", add_shape},
    {"remove_shape", remove_shape},
    {"add_light", add_light},
    {"remove_light", remove_light},
    {"reflection_on", reflection_on},
    {"reflection_off", reflection_off},
    {"shading", shading},
    {"translate", translate},
    {"scale", scale},
    {"shear", shear},
    {"rotate", rotate},
    {"lookat", lookat},
    {"cam", cam},
    {"color", color},
    {"save", save},
    {"axis_on", axis_on},
    {"axis_off", axis_off},
    {"lights_on", lights_on},
    {"lights_off", lights_off},
    {"wire_on", wire_on},
    {"wire_off", wire_off},
    {"quit", quit},
  };

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
    Command command;
    bool exit = false;
    std::string _command, in, name, type;
    glm::vec3 value;

    while (!exit)
    {
      std::getline(std::cin, in);
      std::stringstream ss(in);
      ss >> _command;
      command = str_to_command[_command];

      switch (command)
      {
        case add_shape:
          ss >> type >> name;
          scene.AddObject(type, name);
          break;

        case remove_shape:
          ss >> name;
          scene.RemoveObject(name);
          break;

        case add_light:
          ss >> name >> value.x >> value.y >> value.z;
          scene.AddLight(name, value);
          break;

        case remove_light:
          ss >> name;
          scene.RemoveLight(name);
          break;

        case reflection_on:
          float k;
          ss >> type >> k;
          renderer.SetReflection(type, k);
          break;

        case reflection_off:
          ss >> type;
          renderer.SetReflection(type, 0.0f);
          break;

        case shading:
          ss >> type;
          renderer.SetShading(type);
          break;

        case color:
          ss >> name >> value.x >> value.y >> value.z;
          scene.ChangeObjectColor(name, value);
          break;

        case save:
          ss >> name;
          renderer.SaveScreenshot(name);
          break;

        case translate:
          ss >> name >> value.x >> value.y >> value.z;
          scene.TranslateObject(name, value);
          break;

        case scale:
          ss >> name >> value.x >> value.y >> value.z;
          scene.ScaleObject(name, value);
          break;

        case shear:
          float v0, v1, v2, v3, v4, v5;
          ss >> name >> v0 >> v1 >> v2 >> v3 >> v4 >> v5;
          scene.ShearObject(name, v0, v1, v2, v3, v4, v5);
          break;

        case rotate:
          float angle;
          ss >> name >> angle >> value.x >> value.y >> value.z;
          scene.RotateObject(name, angle, value);
          break;

        case lookat:
          ss >> value.x >> value.y >> value.z;
          scene.SetCameraLookAt(value);
          break;

        case cam:
          ss >> value.x >> value.y >> value.z;
          scene.SetCameraPosition(value);
          break;

        case axis_on:
          renderer.SetAxis(true);
          break;

        case axis_off:
          renderer.SetAxis(false);
          break;

        case lights_on:
          renderer.SetLights(true);
          break;

        case lights_off:
          renderer.SetLights(false);
          break;

        case wire_on:
          renderer.SetWire(true);
          break;

        case wire_off:
          renderer.SetWire(false);
          break;

        case quit:
          exit = true;
          glfwSetWindowShouldClose(window, GLFW_TRUE);
          break;

        default:
          break;
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
