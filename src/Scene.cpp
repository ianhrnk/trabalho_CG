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

std::vector<SceneObject*> Scene::GetObjects()
{ return objects; }

bool Scene::ObjectFound(const std::string &name)
{
  for (it = objects.begin(); it != objects.end(); ++it)
    if ((*it)->GetName() == name)
      return true;
  return false;
}

void Scene::AddObject(const std::string &shape, const std::string &name)
{
  if (!ObjectFound(name))
  {
    SceneObject *object = new SceneObject(shape, name);
    objects.push_back(object);
  }
}

void Scene::RemoveObject(const std::string &name)
{
  if (ObjectFound(name))
    objects.erase(it);
}

void Scene::ChangeObjectColor(const std::string &name, glm::vec3 value)
{
  if (ObjectFound(name))
    (*it)->SetColor(value);
}

void Scene::TranslateObject(const std::string &name, glm::vec3 value)
{
  if (ObjectFound(name))
    (*it)->Translate(value);
}

void Scene::ScaleObject(const std::string &name, glm::vec3 value)
{
  if (ObjectFound(name))
    (*it)->Scale(value);
}

void Scene::ShearObject(const std::string &name, float v0, float v1,
                        float v2, float v3, float v4, float v5)
{
  if (ObjectFound(name))
    (*it)->Shear(v0, v1, v2, v3, v4, v5);
}

void Scene::RotateObject(const std::string &name, float angle,
                         glm::vec3 value)
{
  if (ObjectFound(name))
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
