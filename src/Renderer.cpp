#include "Renderer.h"

Renderer::Renderer(Scene *scene)
{
  this->scene = scene;
  CreateShaders();
}

Renderer::~Renderer()
{
  for (auto it : shader)
    delete it.second;
  shader.clear();
}

void Renderer::CreateShaders()
{
  shader["axis"] = new Shader("shader/axis.vs", "shader/axis.fs");
  shader["none"] = new Shader("shader/none.vs", "shader/none.fs");
  shader["light"] = new Shader("shader/light.vs", "shader/light.fs");
  shader["phong"] = new Shader("shader/phong.vs", "shader/phong.fs");
}

void Renderer::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  if (scene->ShowAxis())
    DrawAxis();

  if (scene->ShowLights())
    DrawLights();

  if (scene->ShowNone())
    DrawObjectsNone();

  if (scene->ShowPhong())
    DrawObjectsPhong();
}

void Renderer::DrawAxis()
{
  SceneObject* axis = scene->GetAxis();
  shader["axis"]->Bind();
  axis->Bind();

  shader["axis"]->SetUniformMatrix4fv("view", scene->GetCamera().GetViewMatrix());
  shader["axis"]->SetUniformMatrix4fv("projection", scene->GetCamera().GetProjectionMatrix());
  shader["axis"]->SetUniformMatrix4fv("model", axis->GetModelMatrix());

  shader["axis"]->SetUniform3f("color", 1.0f, 0.0f, 0.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
  shader["axis"]->SetUniform3f("color", 0.0f, 1.0f, 0.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (const void*)8);
  shader["axis"]->SetUniform3f("color", 0.0f, 0.0f, 1.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (const void*)16);

  axis->Unbind();
  shader["axis"]->Unbind();
}

void Renderer::DrawObjectsNone()
{
  shader["none"]->Bind();

  shader["none"]->SetUniformMatrix4fv("view", scene->GetCamera().GetViewMatrix());
  shader["none"]->SetUniformMatrix4fv("projection", scene->GetCamera().GetProjectionMatrix());

  unsigned int mode = (scene->ShowWire() ? GL_LINE_STRIP : GL_TRIANGLES);
  std::vector<SceneObject*> objects = scene->GetObjects();

  for (auto it = objects.begin(); it != objects.end(); it++)
  {
    (*it)->Bind();
    shader["none"]->SetUniformMatrix4fv("model", (*it)->GetModelMatrix());
    shader["none"]->SetUniform3f("color", (*it)->GetColor());
    glDrawElements(mode, (*it)->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    (*it)->Unbind();
  }

  shader["none"]->Unbind();
}

void Renderer::DrawObjectsPhong()
{
  shader["phong"]->Bind();

  shader["phong"]->SetUniformMatrix4fv("view", scene->GetCamera().GetViewMatrix());
  shader["phong"]->SetUniformMatrix4fv("projection", scene->GetCamera().GetProjectionMatrix());
  shader["phong"]->SetUniform3f("view_position", scene->GetCamera().GetPosition());

  unsigned int mode = (scene->ShowWire() ? GL_LINE_STRIP : GL_TRIANGLES);
  std::vector<SceneObject*> objects = scene->GetObjects();
  std::vector<Light*> lights = scene->GetLights();

  shader["phong"]->SetUniform3f("light_position", lights[0]->GetPosition());
  shader["phong"]->SetUniform3f("light_color", lights[0]->GetColor());

  for (auto it = objects.begin(); it != objects.end(); it++)
  {
      (*it)->Bind();
      shader["phong"]->SetUniformMatrix4fv("model", (*it)->GetModelMatrix());
      shader["phong"]->SetUniform3f("object_color", (*it)->GetColor());
      glDrawElements(mode, (*it)->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
      (*it)->Unbind();
  }
}

void Renderer::DrawLights()
{
  shader["light"]->Bind();

  shader["light"]->SetUniformMatrix4fv("view", scene->GetCamera().GetViewMatrix());
  shader["light"]->SetUniformMatrix4fv("projection", scene->GetCamera().GetProjectionMatrix());

  std::vector<Light*> lights = scene->GetLights();
  for (auto it = lights.begin(); it != lights.end(); it++)
  {
    (*it)->Bind();
    glDrawArrays(GL_POINTS, 0, 3);
    (*it)->Unbind();
  }

  shader["light"]->Unbind();
}
