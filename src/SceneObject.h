#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <limits>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

class SceneObject {
 private:
  std::string name;
  glm::vec3 color = glm::vec3(1.0f);
  glm::mat4 model_matrix = glm::mat4(1.0f);

  VertexArray *vao = nullptr;
  VertexBuffer *vbo = nullptr;
  ElementBuffer *ebo = nullptr;

  void Init(const std::string shape);
  void MergeVerticesNormals(std::vector<float> &buffer,
                            std::vector<float> vertices,
                            std::vector<float> normals,
                            std::map<unsigned int, unsigned int> v_n);
  void LoadObj(const std::string &filename, std::vector<float> &vertices,
              std::vector<float> &normals, std::vector<unsigned int> &indices,
              std::map<unsigned int, unsigned int> &v_n);

 public:
  SceneObject(const std::string &shape, const std::string &name);
  ~SceneObject();

  void Bind();
  void Unbind();

  void Translate(glm::vec3 value);
  void Scale(glm::vec3 value);
  void Shear(float v0, float v1, float v2, float v3, float v4, float v5);
  void Rotate(float angle, glm::vec3 value);

  std::string GetName();
  glm::vec3 GetColor();
  glm::mat4 GetModelMatrix();
  unsigned int GetNumIndices();

  void SetColor(glm::vec3 value);
};

#endif
