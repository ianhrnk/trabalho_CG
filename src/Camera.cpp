#include "Camera.h"

glm::mat4 Camera::GetViewMatrix()
{ return view_matrix; }

glm::mat4 Camera::GetProjectionMatrix()
{ return projection_matrix; }

glm::vec3 Camera::GetPosition()
{ return position; }

void Camera::SetPosition(glm::vec3 value)
{
  position = value;
  Refresh();
}

void Camera::SetTarget(glm::vec3 value)
{
  target = value;
  Refresh();
}

void Camera::Refresh()
{
  view_matrix = glm::lookAt(position, target, up);
}
