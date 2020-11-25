#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <limits>
#include <glm/glm.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

class Model {
 private:
  std::string name;
  glm::vec3 color = glm::vec3(1.0f);
  VertexArray *vao = nullptr;
  VertexBuffer *vbo = nullptr;
  ElementBuffer *ebo = nullptr;

  void CreateAxis();
  void Init(const std::string shape);
  void LoadObj(const std::string &filename, std::vector<float> &vertices,
              std::vector<float> &normais, std::vector<unsigned int> &indices,
              std::map<unsigned int, unsigned int> &vertices_normal);

 public:
  Model(const std::string &shape, const std::string &name);
  ~Model();

  void Bind();
  void Unbind();

  const std::string GetName();
  const glm::vec3 GetColor();
  const unsigned int GetNumIndices();

  void SetColor(float v0, float v1, float v2);
};

#endif
