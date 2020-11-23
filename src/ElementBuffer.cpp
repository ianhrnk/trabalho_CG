#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(unsigned int count, const void* data)
{
  glGenBuffers(1, &id);
  num_elementos = count;
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
  glDeleteBuffers(1, &id);
}

void ElementBuffer::Bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::Unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const unsigned int ElementBuffer::GetNumElementos()
{
  return num_elementos;
}
