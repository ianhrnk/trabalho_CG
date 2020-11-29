#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "SceneObject.h"
#include "Light.h"

class Scene {
 private:
  Camera camera;
  SceneObject* axis;
  std::vector<SceneObject*> objects;
  std::vector<Light*> lights;

  bool show_axis = false;
  bool show_lights = false;  // Não tá definido
  bool show_wire = false;
  bool show_none = true;
  bool show_phong = false;

  std::vector<SceneObject*>::iterator it_object;
  std::vector<Light*>::iterator it_light;

 public:
  Scene();
  ~Scene();

  void DeleteObjects();
  void DeleteLights();

  const std::vector<SceneObject*>& GetObjects() const;
  const std::vector<Light*>& GetLights() const;
  bool ObjectFound(const std::string &name);
  bool LightFound(const std::string &name);

  void AddObject(const std::string &shape, const std::string &name);
  void RemoveObject(const std::string &name);
  void ChangeObjectColor(const std::string &name, glm::vec3 value);

  void TranslateObject(const std::string &name, glm::vec3 value);
  void ScaleObject(const std::string &name, glm::vec3 value);
  void ShearObject(const std::string &name, float v0, float v1,
                   float v2, float v3, float v4, float v5);
  void RotateObject(const std::string &name, float angle, glm::vec3 value);

  void AddLight(const std::string &name, glm::vec3 position);
  void RemoveLight(const std::string &name);

  Camera GetCamera();
  SceneObject* GetAxis();
  bool ShowAxis();
  bool ShowWire();
  bool ShowLights();
  bool ShowNone();
  bool ShowPhong();

  void SetAxis(bool on_off);
  void SetLights(bool on_off);
  void SetWire(bool on_off);
  void SetNone(bool on_off);
  void SetPhong(bool on_off);

  void SetCameraPosition(glm::vec3 value);
  void SetCameraLookAt(glm::vec3 value);
};

#endif
