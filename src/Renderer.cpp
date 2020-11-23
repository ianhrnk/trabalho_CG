#include "Renderer.h"

void Renderer::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EnableDepthTest()
{
  glEnable(GL_DEPTH_TEST);
}
