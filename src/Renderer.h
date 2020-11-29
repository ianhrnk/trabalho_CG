#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Shader.h"

enum ShaderType {
  none, flat, smooth, phong, axis, light
};

class Renderer {
 private:
  Scene *scene = nullptr;
  std::map<ShaderType, Shader*> shader;
  ShaderType shading = none;

  bool show_axis = false;
  bool show_lights = false;
  bool show_wire = false;

  void CreateShaders();
  void SetUniforms(Shader* shader);
  void DrawAxis();
  void DrawObjects();
  void DrawLights();

 public:
  Renderer(Scene *scene);
  ~Renderer();

  void SetAxis(bool on_off);
  void SetLights(bool on_off);
  void SetWire(bool on_off);
  void SetReflection(const std::string &type, float k);
  void SetShading(const std::string &type);

  void Draw();
};

#endif
