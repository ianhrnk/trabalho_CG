#include "Shader.h"

Shader::Shader(const std::string &vertex_file, const std::string &fragment_file) {
  unsigned int vertex_shader = 0;
  unsigned int fragment_shader = 0;

  vertex_shader = LoadAndCompileShader(GL_VERTEX_SHADER, vertex_file);
  fragment_shader = LoadAndCompileShader(GL_FRAGMENT_SHADER, fragment_file);

  this->LinkShaderProgram(vertex_shader, fragment_shader);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

Shader::~Shader() {
  glDeleteProgram(this->id);
}

std::string Shader::LoadShaderSource(const std::string &filename) {
  std::string temp = "";
  std::string src = "";

  std::ifstream in;

  in.open(filename);

  if (in.is_open())
  {
    while (std::getline(in, temp))
      src += temp + "\n";
  }
  else
  {
    std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << filename << '\n';
  }

  in.close();
  return src;
}

unsigned int Shader::LoadAndCompileShader(GLenum type, const std::string &filename) {
  char info_log[512];
  int success;

  unsigned int shader = glCreateShader(type);
  std::string str_src = this->LoadShaderSource(filename);
  const GLchar* src = str_src.c_str();
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << filename << '\n';
    std::cout << info_log << '\n';
  }

  return shader;
}

void Shader::LinkShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader) {
  char info_log[512];
  int success;

  this->id = glCreateProgram();

  glAttachShader(this->id, vertex_shader);
  glAttachShader(this->id, fragment_shader);
  glLinkProgram(this->id);

  glGetProgramiv(this->id, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(this->id, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << '\n';
    std::cout << info_log << '\n';
  }

  glUseProgram(0);
}

void Shader::Bind() { glUseProgram(this->id); }

void Shader::Unbind() { glUseProgram(0); }

int Shader::GetUniformLocation(const std::string& name) {
  int location = glGetUniformLocation(this->id, name.c_str());
  if (location == -1)
    std::cout << "Uniform " << name << " not found!\n";
  return location;
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
  glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
  glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1,
                          float v2, float v3) {
  glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value) {
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
