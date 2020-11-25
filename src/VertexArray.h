#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>

#include "VertexBuffer.h"

class VertexArray {
 private:
  unsigned int id;

 public:
  VertexArray();
  ~VertexArray();

  void Bind();
  void Unbind();
  void AddBuffer(VertexBuffer* vbo);
};

#endif
