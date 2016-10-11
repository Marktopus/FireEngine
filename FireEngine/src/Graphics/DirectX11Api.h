#pragma once
#include "GraphicsApi.h"
#include "DxIncludes.h"
namespace sf
{
  class Window;
}

namespace Fire
{
  class VertexBuffer;
  class Shader;
  class DirectX11Api : public GraphicsApi
  {
    public:
      DirectX11Api();
      ~DirectX11Api();
      void Initialize(sf::Window* window) override;
      void SetMesh(VertexBuffer* vertBuf) override;
      void SetShader(Shader* shader) override;
      void SetTexture() override;

      void BeginScene() override;
      void Render(size_t numVerts) override;
      void EndScene() override;

      void CleanUp() override;

      Shader* MakeShader(const std::string& name);
      VertexBuffer* DirectX11Api::MakeVertexBuffer(
        size_t size, 
        size_t stride, 
        void* src);
    private:
      IDXGISwapChain* d3d_swap_chain_;
      DXGI_SWAP_CHAIN_DESC d3d_description_;
      ID3D11Device* d3d_device_;
      ID3D11DeviceContext* d3d_context_;



      ID3D11RenderTargetView* back_buffer_;
      ID3D11DepthStencilState* depth_stencil_state_;
      ID3D11Texture2D* depth_stencil_buffer_;
      ID3D11DepthStencilView* depth_stencil_view_;
      ID3D11RenderTargetView* render_target_view_;
      ID3D11RasterizerState* rasterizer_state_;

//      ID3D11Buffer* temp_render_buffer_;

      VertexBuffer* temp_vert_buffer_; 
      Shader* temp_shader_;

  };
}