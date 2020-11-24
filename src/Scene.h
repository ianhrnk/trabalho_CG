#ifndef SCENE_H
#define SCENE_H

#include "GL/glew.h"
#include <vector>

#include "Model.h"

class Scene {
 private:
  std::vector<Model*> models;

 public:
  ~Scene();
  void AddModel(const std::string &shape, const std::string &name);
  std::vector<Model*> GetModels();
  std::vector<Model*>::iterator SearchModel(const std::string &name);
  void RemoveModel(const std::string &name);
  void ChangeModelColor(const std::string &name, float v0, float v1, float v2);
};

#endif
