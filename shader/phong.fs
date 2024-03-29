#version 330 core
#define NUM_LIGHTS 10
#define A0 1.0
#define A1 1.0
#define A2 0.25

in vec3 fragment_position;
in vec3 normal;
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
  vec3 view_direction = normalize(view_position - fragment_position);
  vec3 norm = normalize(normal);
  float result = 0.0;

  for (int i = 0; i < num_lights; ++i)
    result += CalcPointLight(lights_positions[i], fragment_position, norm, view_direction);

  // Ambiente
  result += k_ambient;

  fragment_color = vec4((result * object_color), 1.0);
}

float CalcPointLight(vec3 light_pos, vec3 frag_pos, vec3 normal, vec3 view_dir)
{
  // Intensidade da Luz
  float distancia = length(light_pos - frag_pos);
  float light_intensity = 1.0 / (A0 + A1 * distancia + A2 * (distancia * distancia));

  // Difusa
  vec3 light_direction = normalize(light_pos - frag_pos);
  float diff = max(dot(normal, light_direction), 0.0);
  float diffuse = k_diffuse * diff * light_intensity;

  // Especular
  vec3 reflect_direction = reflect(-light_direction, normal);
  float spec = pow(max(dot(view_dir, reflect_direction), 0.0), 32);
  float specular = k_specular * spec * light_intensity;

  return (diffuse + specular);
}