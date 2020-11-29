#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

out vec3 fragment_position;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  fragment_position = vec3(model * vec4(vertex_position, 1.0));
  normal = mat3(transpose(inverse(model))) * vertex_normal;

  gl_Position = projection * view * vec4(fragment_position, 1.0);
}
