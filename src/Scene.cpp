#include "Scene.h"

Scene::Scene()
{
  axis = new SceneObject("axis", "axis");
}

Scene::~Scene()
{
  DeleteObjects();
  DeleteLights();
  delete axis;
}

void Scene::DeleteObjects()
{
  for (auto it : objects)
    delete it;
  objects.clear();
}

void Scene::DeleteLights()
{
  for (auto it : lights)
    delete it;
  lights.clear();
}

const std::vector<SceneObject*>& Scene::GetObjects() const
{ return objects; }

const std::vector<Light*>& Scene::GetLights() const
{ return lights; }

bool Scene::ObjectFound(const std::string &name)
{
  for (it_object = objects.begin(); it_object != objects.end(); ++it_object)
    if ((*it_object)->GetName() == name)
      return true;
  return false;
}

bool Scene::LightFound(const std::string &name)
{
  for (it_light = lights.begin(); it_light != lights.end(); ++it_light)
    if ((*it_light)->GetName() == name)
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
  {
    delete (*it_object);
    objects.erase(it_object);
  }
}

void Scene::ChangeObjectColor(const std::string &name, glm::vec3 value)
{
  if (ObjectFound(name))
    (*it_object)->SetColor(value);
}

void Scene::TranslateObject(const std::string &name, glm::vec3 value)
{
  if (ObjectFound(name))
    (*it_object)->Translate(value);
}

void Scene::ScaleObject(const std::string &name, glm::vec3 value)
{
  if (ObjectFound(name))
    (*it_object)->Scale(value);
}

void Scene::ShearObject(const std::string &name, float v0, float v1,
                        float v2, float v3, float v4, float v5)
{
  if (ObjectFound(name))
    (*it_object)->Shear(v0, v1, v2, v3, v4, v5);
}

void Scene::RotateObject(const std::string &name, float angle,
                         glm::vec3 value)
{
  if (ObjectFound(name))
    (*it_object)->Rotate(angle, value);
}

void Scene::AddLight(const std::string &name, glm::vec3 position)
{
  if (!LightFound(name))
  {
    Light* light = new Light(name, position);
    lights.push_back(light);
  }
}

void Scene::RemoveLight(const std::string &name)
{
  if (LightFound(name))
  {
    delete (*it_light);
    lights.erase(it_light);
  }
}

Camera Scene::GetCamera()
{ return camera; }

SceneObject* Scene::GetAxis()
{ return axis; }

bool Scene::ShowAxis()
{ return show_axis; }

bool Scene::ShowLights()
{ return show_lights; }

bool Scene::ShowWire()
{ return show_wire; }

bool Scene::ShowNone()
{ return show_none; }

bool Scene::ShowPhong()
{ return show_phong; }

void Scene::SetAxis(bool on_off)
{ show_axis = on_off; }

void Scene::SetLights(bool on_off)
{ show_lights = on_off; }

void Scene::SetWire(bool on_off)
{ show_wire = on_off; }

void Scene::SetNone(bool on_off)
{ show_none = on_off; }

void Scene::SetPhong(bool on_off)
{ show_phong = on_off; }

void Scene::SetCameraPosition(glm::vec3 value)
{ camera.SetPosition(value); }

void Scene::SetCameraLookAt(glm::vec3 value)
{ camera.SetTarget(value); }
