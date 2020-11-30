#version 330 core
#define NUM_LIGHTS 10

in vec3 fragment_position;
flat in vec3 face_normal;
out vec4 fragment_color;

uniform vec3 lights_positions[NUM_LIGHTS];
uniform int num_lights;
uniform vec3 view_position;
uniform vec3 object_color;

uniform float k_ambient;
uniform float k_diffuse;
uniform float k_specular;

float CalcPointLight(vec3 light_pos, vec3 frag_pos, vec3 normal, vec3 view_dir);

void main()
{
  vec3 normal = normalize(face_normal);
  vec3 view_direction = normalize(view_position - fragment_position);
  vec3 result = vec3(0.0);

  for (int i = 0; i < num_lights; ++i)
    result += CalcPointLight(lights_positions[i], fragment_position,
            normal, view_direction);

  fragment_color = vec4(result * object_color, 1.0);
}

float CalcPointLight(vec3 light_pos, vec3 frag_pos, vec3 normal, vec3 view_dir)
{
  // Intensidade da luz
  float distance = length(light_pos - frag_pos);
  float light_intensity = 1.0 / (1.0 + 1.0 * distance + 0.25 * (distance * distance));

  // Ambiente
  float ambient = k_ambient;

  // Difusa
  vec3 light_direction = normalize(light_pos - frag_pos);
  float l_n = max(dot(normal, light_direction), 0.0);
  float diffuse = k_diffuse * light_intensity * l_n;

  // Especular
  vec3 reflection_direction = reflect(-light_direction, normal);
  float v_r = pow(max(dot(view_dir, reflection_direction), 0.0), 32);
  float specular = k_specular * light_intensity * v_r;

  return (ambient + diffuse + specular);
}
