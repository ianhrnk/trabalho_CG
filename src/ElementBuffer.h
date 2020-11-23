#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include "GL/glew.h"

class ElementBuffer {
 private:
  unsigned int id;
  unsigned int num_elementos;

 public:
  ElementBuffer(unsigned int count, const void* data);
  ~ElementBuffer();

  void Bind();
  void Unbind();

  const unsigned int GetNumElementos();
};

#endif
