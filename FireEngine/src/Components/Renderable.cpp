#include "Precompiled.h"
#include "Renderable.h"

#include "Graphics/Graphics.h"
#include "Graphics/GraphicsApi.h"
#include "Core/Engine.h"

namespace Fire
{
  Renderable::Renderable(const std::string& mesh, const std::string& shader, const std::string& texture)
  : mesh_name_(mesh),
    shader_name_(shader),
    texture_name_(texture),
    Component(ComponentType::Renderable)
  {

  }

  Renderable::~Renderable()
  {
  
  }
  
  void Renderable::PrepForRender()
  {
    Graphics* graphics = (Graphics*)Engine::GetSystem(SystemType::Graphics);
    graphics->SetMesh(mesh_name_);
    graphics->SetShader(shader_name_);
    graphics->SetTexture(texture_name_);
  }
}