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

  VertexArray *vao = nullptr;
  VertexBuffer *vbo = nullptr;

  void Init();

 public:
  Light(const std::string &name, glm::vec3 position);
  ~Light();

  void Bind();
  void Unbind();

  std::string GetName();
};

#endif
