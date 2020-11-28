#include "Light.h"

Light::Light(const std::string &name, glm::vec3 position)
{
  this->name = name;
  this->position = position;
  Init();
}

Light::~Light()
{
  delete vao;
  delete vbo;
}

void Light::Init()
{
  float pos[] = {
    position.x, position.y, position.z
  };

  vao = new VertexArray();
  vbo = new VertexBuffer(sizeof(pos), pos);
  vao->AddBufferWithoutNormal(vbo);

  vao->Unbind();
  vbo->Unbind();
}

void Light::Bind()
{
  vao->Bind();
}

void Light::Unbind()
{
  vao->Unbind();
}

std::string Light::GetName()
{ return name; }
