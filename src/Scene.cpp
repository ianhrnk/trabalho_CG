#include "Scene.h"

Scene::Scene()
{
  axis = new SceneObject("axis", "axis");
}

Scene::~Scene()
{
  for (auto it = objects.begin(); it != objects.end(); it++)
    delete *it;
  objects.clear();
  delete axis;
}

std::vector<SceneObject*>::iterator
Scene::SearchObject(const std::string &name)
{
  for (auto it = objects.begin(); it != objects.end(); it++)
    if ((*it)->GetName() == name)
      return it;
  return objects.end();
}

std::vector<SceneObject*> Scene::GetObjects()
{ return objects; }

void Scene::AddObject(const std::string &shape, const std::string &name)
{
  if (SearchObject(name) == objects.end())
  {
    SceneObject *object = new SceneObject(shape, name);
    objects.push_back(object);
  }
}

void Scene::RemoveObject(const std::string &name)
{
  std::vector<SceneObject*>::iterator it = SearchObject(name);
  if (it != objects.end())
    objects.erase(it);
}

void Scene::ChangeObjectColor(const std::string &name, glm::vec3 value)
{
  std::vector<SceneObject*>::iterator it = SearchObject(name);
  if (it != objects.end())
    (*it)->SetColor(value);
}

void Scene::TranslateObject(const std::string &name, glm::vec3 value)
{
  std::vector<SceneObject*>::iterator it = SearchObject(name);
  if (it != objects.end())
    (*it)->Translate(value);
}

void Scene::ScaleObject(const std::string &name, glm::vec3 value)
{
  std::vector<SceneObject*>::iterator it = SearchObject(name);
  if (it != objects.end())
    (*it)->Scale(value);
}

void Scene::ShearObject(const std::string &name, float v0, float v1,
                        float v2, float v3, float v4, float v5)
{
  std::vector<SceneObject*>::iterator it = SearchObject(name);
  if (it != objects.end())
    (*it)->Shear(v0, v1, v2, v3, v4, v5);
}

void Scene::RotateObject(const std::string &name, float angle,
                         glm::vec3 value)
{
  std::vector<SceneObject*>::iterator it = SearchObject(name);
  if (it != objects.end())
    (*it)->Rotate(angle, value);
}

Camera Scene::GetCamera()
{ return camera; }

SceneObject* Scene::GetAxis()
{ return axis; }

bool Scene::ShowAxis()
{ return show_axis; }

bool Scene::ShowWire()
{ return show_wire; }

void Scene::SetAxis(bool on_off)
{ show_axis = on_off; }

void Scene::SetWire(bool on_off)
{ show_wire = on_off; }

void Scene::SetCameraPosition(glm::vec3 value)
{ camera.SetPosition(value); }

void Scene::SetCameraLookAt(glm::vec3 value)
{ camera.SetTarget(value); }
