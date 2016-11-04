#pragma once
#include "Core/System.h"

namespace sf
{
  class Window;
}
namespace Fire
{
  class Mesh;
  class GraphicsApi;
  class Texture;
  class Shader;
  class VertexBuffer;
  class Renderable;
  class Camera;
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
      GraphicsApi* GetApi();
      Camera* GetCamera();

      void SetMesh(const std::string& meshName);
      void SetTexture(const std::string& textureName);
      void SetShader(const std::string& shaderName);
    private:
      sf::Window* window_;
      GraphicsApi* api_;

      VertexBuffer* cur_buf_;
      Texture* cur_texture_;
      Shader* cur_shader_;

      std::unordered_map<std::string, Mesh*> meshes_;
      std::unordered_map<std::string, Texture*> textures_;
      std::unordered_map<std::string, Shader*> shaders_;
      std::vector<Renderable*> renderables_;

      Camera* camera_;
  };
}