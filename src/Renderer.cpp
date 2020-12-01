#include "Renderer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"

Renderer::Renderer(Scene *scene)
{
  this->scene = scene;
  CreateShaders();

  // Para girar a imagem verticalmente quando salvar a screenshot
  stbi_flip_vertically_on_write(1);
}

Renderer::~Renderer()
{
  for (auto it : shader)
    delete it.second;
  shader.clear();
}

void Renderer::CreateShaders()
{
  shader[axis] = new Shader("shader/axis.vs", "shader/axis.fs");
  shader[none] = new Shader("shader/none.vs", "shader/none.fs");
  shader[light] = new Shader("shader/light.vs", "shader/light.fs");
  shader[smooth] = new Shader("shader/smooth.vs", "shader/smooth.fs");
  shader[flat] = new Shader("shader/flat.vs", "shader/flat.fs");
  shader[phong] = new Shader("shader/phong.vs", "shader/phong.fs");
}

void Renderer::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glProvokingVertex(GL_FIRST_VERTEX_CONVENTION); // Necessário p/ flat shading

  if (show_axis)
    DrawAxis();

  if (show_lights)
    DrawLights();

  DrawObjects();
}

void Renderer::DrawAxis()
{
  Camera camera = scene->GetCamera();
  SceneObject* _axis = scene->GetAxis();
  shader[axis]->Bind();
  _axis->Bind();

  shader[axis]->SetUniformMatrix4fv("view", camera.GetViewMatrix());
  shader[axis]->SetUniformMatrix4fv("projection", camera.GetProjectionMatrix());

  shader[axis]->SetUniform3f("color", 1.0f, 0.0f, 0.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
  shader[axis]->SetUniform3f("color", 0.0f, 1.0f, 0.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (const void*)(2 * sizeof(unsigned int)));
  shader[axis]->SetUniform3f("color", 0.0f, 0.0f, 1.0f);
  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (const void*)(4 * sizeof(unsigned int)));

  _axis->Unbind();
  shader[axis]->Unbind();
}

void Renderer::DrawLights()
{
  Camera camera = scene->GetCamera();
  shader[light]->Bind();

  shader[light]->SetUniformMatrix4fv("view", camera.GetViewMatrix());
  shader[light]->SetUniformMatrix4fv("projection", camera.GetProjectionMatrix());

  std::vector<Light*> lights = scene->GetLights();
  glPointSize(5.0);
  for (auto it = lights.begin(); it != lights.end(); it++)
  {
    (*it)->Bind();
    glDrawArrays(GL_POINTS, 0, 3);
    (*it)->Unbind();
  }

  shader[light]->Unbind();
}

void Renderer::DrawObjects()
{
  Shader* _shader = shader[shading];
  _shader->Bind();
  SetUniforms(_shader);

  unsigned int mode = (show_wire ? GL_LINE_STRIP : GL_TRIANGLES);
  std::vector<SceneObject*> objects = scene->GetObjects();

  for (auto it = objects.begin(); it != objects.end(); it++)
  {
    (*it)->Bind();
    _shader->SetUniformMatrix4fv("model", (*it)->GetModelMatrix());
    _shader->SetUniform3f("object_color", (*it)->GetColor());
    glDrawElements(mode, (*it)->GetNumIndices(), GL_UNSIGNED_INT, 0);
    (*it)->Unbind();
  }

  _shader->Unbind();
}

void Renderer::SetUniforms(Shader* shader)
{
  Camera camera = scene->GetCamera();
  shader->SetUniformMatrix4fv("view", camera.GetViewMatrix());
  shader->SetUniformMatrix4fv("projection", camera.GetProjectionMatrix());

  if (shading != none)
  {
    std::vector<Light*> lights = scene->GetLights();
    int index = 0;

    shader->SetUniform3f("view_position", camera.GetPosition());
    shader->SetUniform1f("k_ambient", Light::GetKAmbient());
    shader->SetUniform1f("k_diffuse", Light::GetKDiffuse());
    shader->SetUniform1f("k_specular", Light::GetKSpecular());
    shader->SetUniform1i("num_lights", lights.size());

    for (auto it : lights)
    {
      shader->SetUniform3f("lights_positions[" + std::to_string(index) + "]", it->GetPosition());
      index++;
    }
  }
}

void Renderer::SetAxis(bool on_off)
{ show_axis = on_off; }

void Renderer::SetLights(bool on_off)
{ show_lights = on_off; }

void Renderer::SetWire(bool on_off)
{ show_wire = on_off; }

void Renderer::SetReflection(const std::string &type, float k)
{
  if (type == "ambient")
    Light::SetKAmbient(k);
  else if (type == "diffuse")
    Light::SetKDiffuse(k);
  else if (type == "specular")
    Light::SetKSpecular(k);
}

void Renderer::SetShading(const std::string &type)
{
  if (type == "none")
    shading = none;
  else if (type == "smooth")
    shading = smooth;
  else if (type == "flat")
    shading = flat;
  else if (type == "phong")
    shading = phong;
}

void Renderer::SaveScreenshot(const std::string &filename)
{
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  int x = viewport[0];
  int y = viewport[1];
  int width = viewport[2];
  int height = viewport[3];

  char *data = (char*) malloc((size_t) (width * height * 3));

  if (data)
  {
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_write_png(filename.c_str(), width, height, 3, data, 0);
  }

  free(data);
}
