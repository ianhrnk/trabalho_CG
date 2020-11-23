#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "GL/glew.h"

class VertexBuffer {
 private:
  unsigned int id;


 public:
  VertexBuffer(unsigned int size, const void* data);
  ~VertexBuffer();

  void Bind();
  void Unbind();
};

#endif
