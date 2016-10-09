#pragma once

namespace sf
{
  class Window;
}

namespace Fire
{ 
  class GraphicsApi
  { 
    public:
      enum Type
      {
        DX11,
        GL,
        DX12,
        Vulkan
      };

      GraphicsApi(Type apiType);
      virtual ~GraphicsApi();
      virtual Type GetType() final;

      virtual void Initialize(sf::Window*) = 0;
      virtual void Render() = 0;
      virtual void CleanUp() = 0;
      
    private:

      Type api_type_;
      
  };
}