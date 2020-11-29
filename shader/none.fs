#version 330 core
out vec4 fragment_color;

uniform vec3 object_color;

void main()
{
  fragment_color = vec4(object_color, 1.0);
}
