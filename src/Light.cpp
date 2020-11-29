#include "Light.h"

float Light::k_ambient = 0.2f;
float Light::k_diffuse = 0.2f;
float Light::k_specular = 0.2f;

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

glm::vec3 Light::GetPosition()
{ return position; }

float Light::GetKAmbient()
{ return k_ambient; }

float Light::GetKDiffuse()
{ return k_diffuse; }

float Light::GetKSpecular()
{ return k_specular; }

void Light::SetKAmbient(float k)
{ Light::k_ambient = k; }

void Light::SetKDiffuse(float k)
{ Light::k_diffuse = k; }

void Light::SetKSpecular(float k)
{ Light::k_specular = k; }
