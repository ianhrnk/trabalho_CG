#include "Scene.h"

Scene::Scene()
{
  axis = new Model("axis", "axis");
}

Scene::~Scene()
{
  for (auto it = models.begin(); it != models.end(); it++)
    delete *it;
  delete axis;
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
    if ((*it)->GetName() == name)
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

bool Scene::GetShowWire()
{
  return show_wire;
}

void Scene::SetWire(bool on_off)
{
  show_wire = on_off;
}

bool Scene::GetShowAxis()
{
  return show_axis;
}

Model* Scene::GetAxis()
{
  return axis;
}

void Scene::SetAxis(bool on_off)
{
  show_axis = on_off;
}
