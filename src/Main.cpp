#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Renderer.h"
#include "Model.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

int main(void)
{
  GLFWwindow* window;

  // Initialize the library
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(640, 640, "Trabalho", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  //=== Incluir funções de callback aqui ===//

  // Sets the swap interval
  //glfwSwapInterval(3);

  // Initialize the extension entry points
  if(glewInit() != GLEW_OK)
    std::cout << "Error!" << std::endl;

  /* Init section */
  Model model("torus", "teste");

  glm::mat4 identity_matrix(1.0f);
  glm::mat4 model_matrix(1.0f);
  model_matrix = glm::rotate(model_matrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 projection_matrix = glm::ortho(-4.f, 4.f, -4.f, 4.f, 4.f, -4.f);

  // Shader
  Shader shader("shader/main.vs", "shader/main.fs");
  shader.Bind();

  // Init matrices (Uniforms)
  shader.SetUniformMatrix4fv("model", model_matrix);
  shader.SetUniformMatrix4fv("view", identity_matrix);
  shader.SetUniformMatrix4fv("projection", projection_matrix);

  shader.Unbind();

  Renderer::EnableDepthTest();

  /* Loop until the user closes the window - Render section */
  while (!glfwWindowShouldClose(window))
  {
    Renderer::Clear();

    shader.Bind();
    model.Bind();

    // Para ficar rotacionando o cubo
    model_matrix = glm::rotate(model_matrix, glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    shader.SetUniformMatrix4fv("model", model_matrix);

    shader.SetUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); //White
    glDrawElements(GL_TRIANGLES, model.GetNumIndices(), GL_UNSIGNED_INT, nullptr);

    model.Unbind();
    shader.Unbind();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  //render.Finalize();
  glfwTerminate();
  return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
