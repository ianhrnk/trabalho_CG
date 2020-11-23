#include "VertexArray.h"

VertexArray::VertexArray()
{
  glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind()
{
  glBindVertexArray(id);
}

void VertexArray::Unbind()
{
  glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBuffer* vbo)
{
  Bind();
  vbo->Bind();
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)3);
}
