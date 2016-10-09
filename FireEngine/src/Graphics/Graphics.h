#pragma once
#include "Core/System.h"

namespace sf
{
  class Window;
}
namespace Fire
{
  class GraphicsApi;
  class Graphics : public System
  {
    public:
      Graphics();
      ~Graphics();
      void Load();
      void Initialize();
      void Update(float dt);
      void CleanUp();
      void Reinitialize();
    private:
      sf::Window* window_;
      GraphicsApi* api_;
  };
}