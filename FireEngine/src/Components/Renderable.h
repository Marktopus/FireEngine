#pragma once
#include "Core/Component.h"
namespace Fire
{
  class Renderable : public Component
  {
    public:
      Renderable(const std::string& mesh, const std::string& shader, const std::string& texture = "");
      ~Renderable();

      void Initialize(){};
      void Reinitialize(){};
      void Load(){};
      void Update(float dt){};
      void PrepForRender();
    private:
      std::string mesh_name_;
      std::string shader_name_;
      std::string texture_name_;
  };
}