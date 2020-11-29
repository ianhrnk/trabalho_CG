#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Shader.h"

class Renderer {
 private:
  Scene *scene = nullptr;
  std::map<std::string, Shader*> shader;

  void CreateShaders();
  void DrawAxis();
  void DrawObjectsNone();
  void DrawObjectsPhong();
  void DrawLights();

 public:
  Renderer(Scene *scene);
  ~Renderer();

  void Draw();
};

#endif
