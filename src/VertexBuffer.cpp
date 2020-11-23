#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int size, const void* data)
{
  glGenBuffers(1, &id);
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
  glDeleteBuffers(1, &id);
}

void VertexBuffer::Bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
