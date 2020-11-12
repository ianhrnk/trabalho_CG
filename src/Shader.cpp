#include "Shader.h"

Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile) {
  unsigned int vertexShader = 0;
  unsigned int fragmentShader = 0;

  vertexShader = LoadAndCompileShader(GL_VERTEX_SHADER, vertexFile);
  fragmentShader = LoadAndCompileShader(GL_FRAGMENT_SHADER, fragmentFile);

  this->LinkShaderProgram(vertexShader, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() {
  glDeleteProgram(this->id);
}

std::string Shader::LoadShaderSource(const std::string &fileName) {
  std::string temp = "";
  std::string src = "";

  std::ifstream in;

  in.open(fileName);

  if (in.is_open())
  {
    while (std::getline(in, temp))
      src += temp + "\n";
  }
  else
  {
    std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE" << fileName << '\n';
  }
  
  in.close();
  return src;
}

unsigned int Shader::LoadAndCompileShader(GLenum type, const std::string &fileName) {
  char infoLog[512];
  int success;

  unsigned int shader = glCreateShader(type);
  std::string str_src = this->LoadShaderSource(fileName);
  const GLchar* src = str_src.c_str();
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << '\n';
    std::cout << infoLog << '\n';
  }

  return shader;
}

void Shader::LinkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
  char infoLog[512];
  int success;

  this->id = glCreateProgram();

  glAttachShader(this->id, vertexShader);
  glAttachShader(this->id, fragmentShader);
  glLinkProgram(this->id);

  glGetProgramiv(this->id, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(this->id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << '\n';
    std::cout << infoLog << '\n';
  }

  glUseProgram(0);
}

void Shader::Bind() { glUseProgram(this->id); }

void Shader::Unbind() { glUseProgram(0); }

int Shader::GetUniformLocation(const std::string& name) {
  int location = glGetUniformLocation(this->id, name.c_str());
  if (location == -1)
    std::cout << "Uniform '" << name << "' not found!\n";
  return location;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, 
                          float v2, float v3) {
  glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value) {
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
