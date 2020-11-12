// Compile command
// g++ Main.cpp Shader.cpp -o main -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

int main(void)
{ 
  GLFWwindow* window;

  // Initialize the library
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(640, 480, "Cube", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize the extension entry points
  if(glewInit() != GLEW_OK)
    std::cout << "Error!" << std::endl;

  /* Init section */
  float vertices[] = {
    // front
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5,
    // back
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5
  };

  unsigned short indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

  glm::mat4 identity_matrix(1.0f);
  glm::mat4 model_matrix(1.0f);
  model_matrix = glm::rotate(model_matrix, 0.78f, glm::vec3(1.0f, 0.0f, 0.0f));
  model_matrix = glm::rotate(model_matrix, 0.78f, glm::vec3(0.0f, 0.0f, 1.0f));

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  unsigned int IBO;
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Shader
  Shader shader("../shader/main.vp", "../shader/main.fp");
  shader.Bind();

  // Init matrices (Uniforms)
  shader.SetUniformMatrix4fv("model", model_matrix);
  shader.SetUniformMatrix4fv("view", identity_matrix);
  shader.SetUniformMatrix4fv("projection", identity_matrix);  

  shader.Unbind();
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  

  /* Loop until the user closes the window - Render section */
  while (!glfwWindowShouldClose(window))
  {
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    shader.Bind();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    shader.SetUniform4f("u_Color", 1.0f, 0.67f, 0.67f, 1.0f); //Red
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    shader.SetUniform4f("u_Color", 1.0f, 0.83f, 0.64f, 1.0f); //Orange
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void*)12);
    shader.SetUniform4f("u_Color", 0.99f, 1.0f, 0.71f, 1.0f); //Yellow
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void*)24);
    shader.SetUniform4f("u_Color", 0.79f, 1.0f, 0.74f, 1.0f);  //Green
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void*)36);
    shader.SetUniform4f("u_Color", 0.60f, 0.96f, 1.0f, 1.0f);  //Blue
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void*)48);
    shader.SetUniform4f("u_Color", 1.0f, 0.77, 1.0f, 1.0f); //Pink
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void*)48);

    shader.Unbind();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
