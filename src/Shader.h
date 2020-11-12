#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <iostream>

class Shader
{
 private:
  unsigned int id;

  std::string LoadShaderSource(const std::string &fileName);
  unsigned int LoadAndCompileShader(GLenum type, const std::string &fileName);
  void LinkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

  int GetUniformLocation(const std::string& name);

 public:
  Shader(const std::string &vertexFile, const std::string &fragmentFile);
  ~Shader();
  void Bind();
  void Unbind();

  // Uniform functions
  void SetUniform4f(const std::string& name, float v0, float v1, 
                    float v2, float v3);
  void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);
};
