#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <string>

#include "VertexArray.h"
#include "VertexBuffer.h"

class Light {
 private:
  std::string name;
  glm::vec3 position;

  VertexArray *vao = nullptr;
  VertexBuffer *vbo = nullptr;

  static float k_ambient;
  static float k_diffuse;
  static float k_specular;

  void Init();

 public:
  Light(const std::string &name, glm::vec3 position);
  ~Light();

  void Bind();
  void Unbind();

  std::string GetName();
  glm::vec3 GetPosition();
  static float GetKAmbient();
  static float GetKDiffuse();
  static float GetKSpecular();

  static void SetKAmbient(float k);
  static void SetKDiffuse(float k);
  static void SetKSpecular(float k);
};

#endif
