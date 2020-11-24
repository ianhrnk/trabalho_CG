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
  bool SearchModel(const std::string &name);
};

#endif
