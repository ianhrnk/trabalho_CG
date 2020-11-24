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

  std::string LoadShaderSource(const std::string &filename);
  unsigned int LoadAndCompileShader(GLenum type, const std::string &filename);
  void LinkShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);

  int GetUniformLocation(const std::string& name);

 public:
  Shader(const std::string &vertex_file, const std::string &fragment_file);
  ~Shader();
  void Bind();
  void Unbind();
  void InitMatrices();

  // Uniform functions
  void SetUniform1f(const std::string& name, float v0);
  void SetUniform3f(const std::string& name, float v0, float v1,
                    float v2);
  void SetUniform3f(const std::string&name, glm::vec3 vec);
  void SetUniform4f(const std::string& name, float v0, float v1,
                    float v2, float v3);
  void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);
};
