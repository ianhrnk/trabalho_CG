#include "Scene.h"

Scene::Scene()
{
  axis = new SceneObject("axis", "axis");
}

Scene::~Scene()
{
  for (auto it = objects.begin(); it != objects.end(); it++)
    delete *it;
  delete axis;
}

void Scene::AddObject(const std::string &shape, const std::string &name)
{
  if (SearchObject(name) == objects.end())
  {
    SceneObject *object = new SceneObject(shape, name);
    objects.push_back(object);
  }
}

std::vector<SceneObject*> Scene::GetObjects()
{
  return objects;
}

std::vector<SceneObject*>::iterator Scene::SearchObject(const std::string &name)
{
  for (auto it = objects.begin(); it != objects.end(); it++)
    if ((*it)->GetName() == name)
      return it;
  return objects.end();
}

void Scene::RemoveObject(const std::string &name)
{
  std::vector<SceneObject*>::iterator it = SearchObject(name);
  if (it != objects.end())
    objects.erase(it);
}

void Scene::ChangeObjectColor(const std::string &name, float v0, float v1, float v2)
{
  std::vector<SceneObject*>::iterator it = SearchObject(name);
  if (it != objects.end())
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

SceneObject* Scene::GetAxis()
{
  return axis;
}

void Scene::SetAxis(bool on_off)
{
  show_axis = on_off;
}
