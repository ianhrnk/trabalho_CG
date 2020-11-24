#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <limits>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

class Model {
 private:
  std::string name;
  VertexArray *vao;
  VertexBuffer *vbo;
  ElementBuffer *ebo;

  void Init(const std::string shape);
  void LoadObj(const std::string &filename, std::vector<float> &vertices,
              std::vector<float> &normais, std::vector<unsigned int> &indices,
              std::map<unsigned int, unsigned int> &vertices_normal);

 public:
  Model(const std::string &shape, const std::string &name);
  ~Model();
  void Bind();
  void Unbind();
  const unsigned int GetNumIndices();
};

#endif
