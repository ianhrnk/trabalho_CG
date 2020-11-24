#include "Renderer.h"

Renderer::Renderer(Shader *shader, Scene *scene) //Scene scene, Camera camera
{
  this->scene = scene;
  this->shader = shader;
}

Renderer::~Renderer()
{

}

void Renderer::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  shader->Bind();

  std::vector<Model*> models = scene->GetModels();
  for (auto it = models.begin(); it != models.end(); it++)
  {
    (*it)->Bind();
    glDrawElements(GL_TRIANGLES, (*it)->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    (*it)->Unbind();
  }

  shader->Unbind();
}
