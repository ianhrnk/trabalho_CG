#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <string>

#include "VertexArray.h"
#include "VertexBuffer.h"

class Light {
 private:
  std::string name;
  glm::vec3 position;
  glm::vec3 color = glm::vec3(1.0f);

  VertexArray *vao = nullptr;
  VertexBuffer *vbo = nullptr;

  void Init();

 public:
  Light(const std::string &name, glm::vec3 position);
  ~Light();

  void Bind();
  void Unbind();

  std::string GetName();
  glm::vec3 GetPosition();
  glm::vec3 GetColor();
};

#endif
