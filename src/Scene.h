#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <vector>

#include "Camera.h"
#include "SceneObject.h"

class Scene {
 private:
  Camera camera;
  SceneObject* axis;
  std::vector<SceneObject*> objects;
  bool show_axis = false;
  bool show_wire = false;

 public:
  Scene();
  ~Scene();

  std::vector<SceneObject*>::iterator SearchObject(const std::string &name);
  std::vector<SceneObject*> GetObjects();

  void AddObject(const std::string &shape, const std::string &name);
  void RemoveObject(const std::string &name);
  void ChangeObjectColor(const std::string &name, glm::vec3 value);

  void TranslateObject(const std::string &name, glm::vec3 value);
  void ScaleObject(const std::string &name, glm::vec3 value);
  void ShearObject(const std::string &name, float v0, float v1,
                   float v2, float v3, float v4, float v5);
  void RotateObject(const std::string &name, float angle, glm::vec3 value);

  Camera GetCamera();
  SceneObject* GetAxis();
  bool ShowAxis();
  bool ShowWire();

  void SetAxis(bool on_off);
  void SetWire(bool on_off);
  void SetCameraPosition(glm::vec3 value);
  void SetCameraLookAt(glm::vec3 value);
};

#endif
