#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int count, const void* data)
{
  glGenBuffers(1, &id);
  Bind();
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
  Unbind();
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
