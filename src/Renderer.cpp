#include "Renderer.h"

Renderer::Renderer(Shader *shader, Scene *scene)
{
  this->scene = scene;
  this->shader = shader;
}

Renderer::~Renderer()
{
  // TODO
}

void Renderer::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  shader->Bind();

  // Para desenhar os eixos
  if (scene->GetShowAxis())
  {
    Model* axis = scene->GetAxis();
    axis->Bind();
    shader->SetUniform3f("color", 1.0f, 0.0f, 0.0f);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
    shader->SetUniform3f("color", 0.0f, 1.0f, 0.0f);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (const void*)8);
    shader->SetUniform3f("color", 0.0f, 0.0f, 1.0f);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (const void*)16);
    axis->Unbind();
  }

  // Para desenhar todos os objetos da cena
  std::vector<Model*> models = scene->GetModels();
  unsigned int mode = (scene->GetShowWire() ? GL_LINES : GL_TRIANGLES);
  for (auto it = models.begin(); it != models.end(); it++)
  {
    (*it)->Bind();
    shader->SetUniform3f("color", (*it)->GetColor());
    glDrawElements(mode, (*it)->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    (*it)->Unbind();
  }

  shader->Unbind();
}
