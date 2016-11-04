#include "Precompiled.h"
#include "DirectX11Api.h"
#include "DxBuffers.h"
#include "DxShader.h"

#include "SFML/Window.hpp"
#include "Math/Vector4.h"
namespace Fire
{
  DirectX11Api::DirectX11Api() : GraphicsApi(ApiType::DX11)
  {

  }

  DirectX11Api::~DirectX11Api()
  {
                     
  }

  void DirectX11Api::Initialize(sf::Window* window)
  {
    auto windowSize = window->getSize();
    SecureZeroMemory(&d3d_description_, sizeof(d3d_description_));
    d3d_description_.BufferCount = 1;                                 // # of backbuffers
    d3d_description_.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // 32 bit color
    //TODO: point to window class, or pass size
    d3d_description_.BufferDesc.Width = windowSize.x;
    d3d_description_.BufferDesc.Height = windowSize.y;
    d3d_description_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // swap chain use
    d3d_description_.OutputWindow = window->getSystemHandle();        // output window
    d3d_description_.SampleDesc.Count = 1;                            // auto anti aliasing, tweakable
    d3d_description_.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevels[] =
    {
      D3D_FEATURE_LEVEL_11_0
    };
    D3D_FEATURE_LEVEL supportedLevel;
    auto error = D3D11CreateDeviceAndSwapChain(
      nullptr,                  // adapter pointer. nullptr means default
      D3D_DRIVER_TYPE_HARDWARE, // driver type. we want hardware.
      nullptr,                  // software rasterizer. used if previous parameter is D3D_DRIVER_TYPE_SOFTWARE
      D3D11_CREATE_DEVICE_DEBUG,// device flags. got none atm.
      featureLevels,            // feature level array goes here. using default array.
      ARRAYSIZE(featureLevels), // number of elements in the feature level array
      D3D11_SDK_VERSION,        // current sdk version (we're in 11)
      &d3d_description_,        // description pointer (will be filled)
      &d3d_swap_chain_,         // swap chain (will be filled)
      &d3d_device_,             // device (will be filled)
      &supportedLevel,          // feature level pointer. we don't care atm.
      &d3d_context_);           // device context (will be filled

    if(error != S_OK) 
    {
      __debugbreak();
    }
    ID3D11Texture2D* backBuffer;

    error = d3d_swap_chain_->GetBuffer( 0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    if(error != S_OK)
    {
      __debugbreak();
    }

    error = d3d_device_->CreateRenderTargetView(backBuffer, nullptr, &render_target_view_);
    if(error != S_OK) 
    {
      __debugbreak();
    }
    backBuffer->Release();
    backBuffer = nullptr;

    D3D11_TEXTURE2D_DESC depthBufferDesc;
    SecureZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
    depthBufferDesc.Width = windowSize.x;
    depthBufferDesc.Height = windowSize.y;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    SecureZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

    // Set up the description of the stencil state.
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

    depthStencilDesc.StencilEnable = true;
    depthStencilDesc.StencilReadMask = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;

    // Stencil operations if pixel is front-facing.
    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Stencil operations if pixel is back-facing.
    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


    error = d3d_device_->CreateDepthStencilState(&depthStencilDesc, &depth_stencil_state_);

    if(error != S_OK) 
    {
      __debugbreak();
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

    // Set up the depth stencil view description.
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // Create the depth stencil view.
    error = d3d_device_->CreateTexture2D(&depthBufferDesc, NULL, &depth_stencil_buffer_);
    if(error != S_OK) 
    {
      __debugbreak();
    }
    error = d3d_device_->CreateDepthStencilView(
      depth_stencil_buffer_,
      &depthStencilViewDesc,
      &depth_stencil_view_);
    if(error != S_OK) 
    {
      __debugbreak();
    }
    d3d_context_->OMSetRenderTargets(1, &render_target_view_, depth_stencil_view_);

    D3D11_RASTERIZER_DESC rasterDesc;
    SecureZeroMemory(&rasterDesc, sizeof(rasterDesc));
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = true;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    // Create the rasterizer state from the description we just filled out.
    error = d3d_device_->CreateRasterizerState(&rasterDesc, &rasterizer_state_);

    if(error != S_OK)
    {
      __debugbreak();
    }
    d3d_context_->RSSetState(rasterizer_state_);

    D3D11_VIEWPORT viewport;
    viewport.Width = (float)windowSize.x;
    viewport.Height = (float) windowSize.y;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    // Create the viewport.
    d3d_context_->RSSetViewports(1, &viewport);

  }

  void DirectX11Api::SetMesh(VertexBuffer* vertBuf)
  {
    unsigned stride = vertBuf->GetStride();
    unsigned offset = 0;
    ID3D11Buffer* buf = (ID3D11Buffer*)vertBuf->GetBufferPointer();
    d3d_context_->IASetVertexBuffers(0, 1, &buf, &stride, &offset);
    d3d_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  }

  void DirectX11Api::SetShader(Shader* shader)
  {
    ID3D11InputLayout* layout = (ID3D11InputLayout*)shader->GetLayoutPointer();
    d3d_context_->IASetInputLayout(layout);

    ID3D11VertexShader* vert = (ID3D11VertexShader*)shader->GetVertPointer();
    d3d_context_->VSSetShader(vert, 0, 0);
    ID3D11PixelShader* pix = (ID3D11PixelShader*)shader->GetPixPointer();
    d3d_context_->PSSetShader(pix, 0, 0);
    shader->UpdateBuffers();
    shader->PreRender();
  }

  void DirectX11Api::SetTexture()
  {

  }

  void DirectX11Api::BeginScene()
  {
    // Clear the back buffer.
    d3d_context_->ClearRenderTargetView(render_target_view_, Vector4(0.0f, 1.0f, 0.0f, 1.0f).v);
    // Clear the depth buffer.
    d3d_context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
  }

  void DirectX11Api::Render(size_t numVerts)
  {
    d3d_context_->Draw(numVerts, 0);
  }

  void DirectX11Api::EndScene()
  {
    d3d_swap_chain_->Present(0, 0);
  }

  void DirectX11Api::CleanUp()
  {

  }

  Shader* DirectX11Api::MakeShader(const std::string& name)
  {
    DxShader* newShader = new DxShader(name);
    newShader->Compile(d3d_device_);

    return (Shader*)newShader;
  }

  VertexBuffer* DirectX11Api::MakeVertexBuffer(
    size_t size, 
    size_t stride, 
    void* src)
  {
    return (VertexBuffer*)new DxVertexBuffer(size, stride, src);
  }

  ID3D11Device* DirectX11Api::GetDevice()
  {
    return d3d_device_;
  }

  ID3D11DeviceContext* DirectX11Api::GetDeviceContext()
  {
    return d3d_context_;
  }
}
