#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
 private:
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 view_matrix = glm::lookAt(position, target, up);
  glm::mat4 projection_matrix = glm::ortho(-2.f, 2.f, -2.f, 2.f, -2.f, 2.f);

  void Refresh();

 public:
  Camera() = default;
  ~Camera() = default;

  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix();
  glm::vec3 GetPosition();

  void SetPosition(glm::vec3 value);
  void SetTarget(glm::vec3 value);
};

#endif
