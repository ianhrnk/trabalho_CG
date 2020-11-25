#include "Renderer.h"

Renderer::Renderer(Shader *shader, Scene *scene)
{
  this->scene = scene;
  this->shader = shader;
}

void Renderer::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  shader->Bind();

  shader->SetUniformMatrix4fv("view", scene->GetCamera().GetViewMatrix());
  shader->SetUniformMatrix4fv("projection", scene->GetCamera().GetProjectionMatrix());

  if (scene->ShowAxis())
    DrawAxis();
  DrawObjects();

  shader->Unbind();
}

void Renderer::DrawAxis()
{
  SceneObject* axis = scene->GetAxis();
  axis->Bind();
  shader->SetUniformMatrix4fv("model", axis->GetModelMatrix());
  shader->SetUniform3f("color", 1.0f, 0.0f, 0.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
  shader->SetUniform3f("color", 0.0f, 1.0f, 0.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (const void*)8);
  shader->SetUniform3f("color", 0.0f, 0.0f, 1.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (const void*)16);
  axis->Unbind();
}

void Renderer::DrawObjects()
{
  unsigned int mode = (scene->ShowWire() ? GL_LINE_STRIP : GL_TRIANGLES);
  std::vector<SceneObject*> objects = scene->GetObjects();
  for (auto it = objects.begin(); it != objects.end(); it++)
  {
    (*it)->Bind();
    shader->SetUniformMatrix4fv("model", (*it)->GetModelMatrix());
    shader->SetUniform3f("color", (*it)->GetColor());
    glDrawElements(mode, (*it)->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    (*it)->Unbind();
  }
}
