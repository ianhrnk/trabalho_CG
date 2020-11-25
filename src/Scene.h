#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <vector>

#include "SceneObject.h"

class Scene {
 private:
  SceneObject* axis;
  std::vector<SceneObject*> objects;
  bool show_axis = false;
  bool show_wire = false;

 public:
  Scene();
  ~Scene();

  void AddObject(const std::string &shape, const std::string &name);
  void RemoveObject(const std::string &name);
  void ChangeObjectColor(const std::string &name, glm::vec3 value);
  void RotateObject(const std::string &name, float angle, glm::vec3 value);
  std::vector<SceneObject*>::iterator SearchObject(const std::string &name);
  std::vector<SceneObject*> GetObjects();

  bool GetShowWire();
  bool GetShowAxis();
  SceneObject* GetAxis();

  void SetWire(bool on_off);
  void SetAxis(bool on_off);
};

#endif
