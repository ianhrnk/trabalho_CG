#include "Scene.h"

Scene::~Scene()
{
  for (auto it = models.begin(); it != models.end(); it++)
    delete *it;
}

void Scene::AddModel(const std::string &shape, const std::string &name)
{
  Model *model = new Model(shape, name);
  models.push_back(model);
}

std::vector<Model*> Scene::GetModels()
{
  return models;
}

bool Scene::SearchModel(const std::string &name)
{
  for (auto it = models.begin(); it != models.end(); it++)
    if (((*it)->GetName()).compare(name) == 0)
      return true;
  return false;
}
