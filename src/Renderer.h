#ifndef RENDERER_H
#define RENDERER_H

#include "GL/glew.h"

#include "Scene.h"
#include "Shader.h"

class Renderer {
 private:
  Scene *scene = nullptr;
  Shader *shader = nullptr;

 public:
  Renderer(Shader *shader, Scene *scene); //Adicionar camera
  ~Renderer();
  void Draw();
  //void Finalize();
};

#endif
