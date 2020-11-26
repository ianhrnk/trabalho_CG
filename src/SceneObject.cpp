#include "SceneObject.h"

Reader SceneObject::reader;

SceneObject::SceneObject(const std::string &shape, const std::string &name)
{
  this->name = name;
  Init(shape);
}

SceneObject::~SceneObject()
{
  delete vao;
  delete vbo;
  delete ebo;
}

void SceneObject::Init(const std::string shape)
{
  Object obj;
  obj = SceneObject::reader.LoadObj(shape);

  vao = new VertexArray();
  vbo = new VertexBuffer(obj.vertices.size(), obj.vertices.data());
  vao->AddBuffer(vbo);
  ebo = new ElementBuffer(obj.indices.size(), obj.indices.data());

  vao->Unbind();
  vbo->Unbind();
  ebo->Unbind();
}

void SceneObject::Bind()
{
  vao->Bind();
  ebo->Bind();
}

void SceneObject::Unbind()
{
  vao->Unbind();
  ebo->Unbind();
}

void SceneObject::Translate(glm::vec3 value)
{
  model_matrix = glm::translate(model_matrix, value);
}

void SceneObject::Scale(glm::vec3 value)
{
  model_matrix = glm::scale(model_matrix, value);
}

void SceneObject::Shear(float v0, float v1, float v2, float v3,
                        float v4, float v5)
{
  model_matrix = glm::shearX3D(model_matrix, v0, v1);
  model_matrix = glm::shearY3D(model_matrix, v2, v3);
  model_matrix = glm::shearZ3D(model_matrix, v4, v5);
}

void SceneObject::Rotate(float angle, glm::vec3 value)
{
  model_matrix = glm::rotate(model_matrix, glm::radians(angle), value);
}

unsigned int SceneObject::GetNumIndices()
{ return ebo->NumElementos(); }

std::string SceneObject::GetName()
{ return name; }

glm::vec3 SceneObject::GetColor()
{ return color; }

glm::mat4 SceneObject::GetModelMatrix()
{ return model_matrix; }

void SceneObject::SetColor(glm::vec3 value)
{ color = value; }
