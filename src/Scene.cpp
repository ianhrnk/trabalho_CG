#include "Scene.h"

Scene::~Scene()
{
  for (auto it = models.begin(); it != models.end(); it++)
    delete *it;
}

void Scene::AddModel(const std::string &shape, const std::string &name)
{
  if (SearchModel(name) == models.end())
  {
    Model *model = new Model(shape, name);
    models.push_back(model);
  }
}

std::vector<Model*> Scene::GetModels()
{
  return models;
}

std::vector<Model*>::iterator Scene::SearchModel(const std::string &name)
{
  for (auto it = models.begin(); it != models.end(); it++)
    if (((*it)->GetName()).compare(name) == 0)
      return it;
  return models.end();
}

void Scene::RemoveModel(const std::string &name)
{
  std::vector<Model*>::iterator it = SearchModel(name);
  if (it != models.end())
    models.erase(it);
}

void Scene::ChangeModelColor(const std::string &name, float v0, float v1, float v2)
{
  std::vector<Model*>::iterator it = SearchModel(name);
  if (it != models.end())
    (*it)->SetColor(v0, v1, v2);
}
