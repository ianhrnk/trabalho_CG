#version 330 core
layout (location = 0) in vec3 axis_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * vec4(axis_position, 1.0);
}
