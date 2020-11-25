#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include "Scene.h"
#include "Shader.h"

class Renderer {
 private:
  Scene *scene = nullptr;
  Shader *shader = nullptr;

  void DrawAxis();
  void DrawObjects();

 public:
  Renderer(Shader *shader, Scene *scene);
  ~Renderer() = default;

  void Draw();
};

#endif
