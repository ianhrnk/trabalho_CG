#ifndef SCENE_H
#define SCENE_H

#include "GL/glew.h"
#include <vector>

#include "Model.h"

class Scene {
 private:
  Model* axis;
  std::vector<Model*> models;
  bool show_axis = false;
  bool show_wire = false;

 public:
  Scene();
  ~Scene();

  void AddModel(const std::string &shape, const std::string &name);
  std::vector<Model*> GetModels();
  std::vector<Model*>::iterator SearchModel(const std::string &name);
  void RemoveModel(const std::string &name);
  void ChangeModelColor(const std::string &name, float v0, float v1, float v2);

  bool GetShowWire();
  bool GetShowAxis();
  Model* GetAxis();

  void SetWire(bool on_off);
  void SetAxis(bool on_off);
};

#endif
