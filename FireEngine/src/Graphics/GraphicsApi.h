#pragma once

namespace sf
{
  class Window;
}


namespace Fire
{
  class Shader;
  class VertexBuffer;
  namespace ApiType
  {
    enum Enum
    {
      DX11,
      GL,
      DX12,
      Vulkan,
      Count
    };
  } 
  class GraphicsApi
  { 
    public:

      GraphicsApi(ApiType::Enum apiType);
      virtual ~GraphicsApi();
      ApiType::Enum GetType();
      virtual void Initialize(sf::Window*) = 0;

      virtual void SetMesh(VertexBuffer* vertBuf) = 0;
      virtual void SetShader(Shader* vertBuf) = 0;
      virtual void SetTexture() = 0;

      virtual void BeginScene() = 0;
      virtual void Render(size_t numVerts) = 0;
      virtual void EndScene() = 0;

      virtual void CleanUp() = 0;
      
      virtual Shader* MakeShader(const std::string& name) = 0;
      virtual VertexBuffer* MakeVertexBuffer(
        size_t size, 
        size_t stride, 
        void* src = nullptr) = 0;
    private:

      ApiType::Enum api_type_;
      
  };
}