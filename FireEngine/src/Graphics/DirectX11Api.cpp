#include "Precompiled.h"
#include "DirectX11Api.h"


#include "SFML/Window.hpp"
#include "Math/Vector4.h"
namespace Fire
{
  DirectX11Api::DirectX11Api() : GraphicsApi(GraphicsApi::DX11)
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



    //   BUFFER INIT
    Vector4* vertices = new Vector4[3];
    vertices[0] = Vector4(0.0, 0.0, 0.0, 1.0);
    vertices[1] = Vector4(1.0, 0.0, 0.0, 1.0);
    vertices[2] = Vector4(1.0, 1.0, 0.0, 1.0);

    D3D11_BUFFER_DESC bufferDesc;
    SecureZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
    D3D11_SUBRESOURCE_DATA* buffData = nullptr;

    bufferDesc.ByteWidth = sizeof(float) * 4 * 3;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    buffData = (D3D11_SUBRESOURCE_DATA*) alloca(sizeof(D3D11_SUBRESOURCE_DATA));
    SecureZeroMemory(buffData, sizeof(D3D11_SUBRESOURCE_DATA));
    buffData->pSysMem = vertices;

    


    error = d3d_device_->CreateBuffer(
      &bufferDesc,
      buffData,
      &temp_render_buffer_);

    if(error != S_OK)
    {
      __debugbreak();
    }
    //SHADER INIT
   
    ID3D10Blob* errorMsg; 
    ID3D10Blob* vertShaderBuf; 
    std::string shaderFile("src/shaders/color.vs");
    std::wstring dxName(shaderFile.begin(), shaderFile.end());
    error = D3DCompileFromFile(
      dxName.c_str(),
      NULL,
      NULL,
      "main",
      "vs_5_0",
    #ifdef _DEBUG
      D3D10_SHADER_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
    #elif _RELEASE
      D3D10_SHADER_ENABLE_STRICTNESS,
    #endif
      0,
      &vertShaderBuf,
      &errorMsg);
    
    if(error != S_OK) 
    {
      __debugbreak();
    }
    if(errorMsg)
    {
      //error?
      if(vertShaderBuf)
      {
        vertShaderBuf->Release();
      }
      std::cout << "shader " << shaderFile << "failed to compile with error" << (char*)errorMsg->GetBufferPointer() << std::endl;
      errorMsg->Release();
    }
    else
    {
      error = d3d_device_->CreateVertexShader(
        vertShaderBuf->GetBufferPointer(), 
        vertShaderBuf->GetBufferSize(), 
        nullptr, 
        &temp_vert_shader_);  
      if(error)
      {
        __debugbreak();
      }
    }


    struct ParamTypeInfo
    {
      std::string name;
      size_t size;
      size_t offset;
    };


    ID3D11ShaderReflection* vertShaderReflection = nullptr;
    error = D3DReflect(
      vertShaderBuf->GetBufferPointer(),
      vertShaderBuf->GetBufferSize(),
      IID_ID3D11ShaderReflection,
      (void**) &vertShaderReflection);

    if(error != S_OK)
    {
      __debugbreak();
    }

    D3D11_SHADER_DESC shaderDesc;
    error = vertShaderReflection->GetDesc(&shaderDesc);

    if(error != S_OK)
    {
      __debugbreak();
    }
    // Read input layout description from shader info
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
    for(unsigned i = 0; i < shaderDesc.InputParameters; i++)
    {
      ParamTypeInfo newParam;
      D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
      error = vertShaderReflection->GetInputParameterDesc(i, &paramDesc); 
      if(error != S_OK)
      {
        __debugbreak();
      }

      // fill out input element desc
      D3D11_INPUT_ELEMENT_DESC elementDesc;
      SecureZeroMemory(&elementDesc, sizeof(elementDesc));
      elementDesc.SemanticName = paramDesc.SemanticName;
      elementDesc.SemanticIndex = paramDesc.SemanticIndex;
      elementDesc.InputSlot = 0;
      elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
      elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
      elementDesc.InstanceDataStepRate = 0;
      if(paramDesc.Mask == 1)
      {
        if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
      }
      else if(paramDesc.Mask <= 3)
      {
        if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
      else if(paramDesc.Mask <= 7)
      {
        if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
      else if(paramDesc.Mask <= 15)
      {
        if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
      inputLayoutDesc.push_back(elementDesc);
    }







    //for(size_t i = 0; i < shaderDesc.ConstantBuffers; i++)
    //{
    //  ID3D11ShaderReflectionConstantBuffer* pConstantReflection = vertShaderReflection->GetConstantBufferByIndex(i);
    //  D3D11_SHADER_BUFFER_DESC desc;
    //  error = pConstantReflection->GetDesc(&desc);
    //  if(error != S_OK)
    //  {
    //    __debugbreak();
    //  }

    //  D3D11_BUFFER_DESC bufferDesc;
    //  SecureZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
    //  D3D11_SUBRESOURCE_DATA* buffData = nullptr;

    //  bufferDesc.ByteWidth = sizeof(float) * 4 * 3;
    //  bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    //  bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    //  bufferDesc.Usage = D3D11_USAGE_DYNAMIC;

    //  d3d_device_->CreateBuffer(
    //    &bufferDesc,
    //    buffData,
    //    &temp_render_buffer_);

    //  for(size_t varInd = 0; varInd < desc.Variables; ++varInd)
    //  {
    //    ID3D11ShaderReflectionVariable* curVar = pConstantReflection->GetVariableByIndex(varInd);
    //    D3D11_SHADER_VARIABLE_DESC varDesc;
    //    error = curVar->GetDesc(&varDesc);
    //    if(error != S_OK)
    //    {
    //      __debugbreak();
    //    }

    //    newBuf->AddParameter({varDesc.Name, varDesc.Size, varDesc.StartOffset});

    //  }
    //  newBuf->Initialize();
    //  AddConstantBuffer(newBuf);
    //  //m_cBuffer[i] = new d3d::ConstantBuffer(*m_pDevice, desc.Size);
    //}
    //int bufSize = shaderBuf->GetBufferSize();
    error = d3d_device_->CreateInputLayout(
      &inputLayoutDesc[0],
      inputLayoutDesc.size(),
      vertShaderBuf->GetBufferPointer(),
      vertShaderBuf->GetBufferSize(),
      &layout_);

    if(error)
    {
      __debugbreak();
    }





    ID3D10Blob* pixShaderBuf; 

    shaderFile = "src/shaders/color.ps";
    dxName.assign(shaderFile.begin(), shaderFile.end());
    error = D3DCompileFromFile(
      dxName.c_str(),
      NULL,
      NULL,
      "main",
      "ps_5_0",
    #ifdef _DEBUG
      D3D10_SHADER_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
    #elif _RELEASE
      D3D10_SHADER_ENABLE_STRICTNESS,
    #endif
      0,
      &pixShaderBuf,
      &errorMsg);

    if(error != S_OK)
    {
      __debugbreak();
    }
    if(errorMsg)
    {
      //error?
      if(pixShaderBuf)
      {
        pixShaderBuf->Release();
      }
      std::cout << "shader " << shaderFile << "failed to compile with error" << (char*) errorMsg->GetBufferPointer() << std::endl;
      errorMsg->Release();
    }
    else
    {
      error = d3d_device_->CreatePixelShader(
        pixShaderBuf->GetBufferPointer(),
        pixShaderBuf->GetBufferSize(),
        nullptr,
        &temp_pix_shader_);
      if(error)
      {
        __debugbreak();
      }

    }
  }

  void DirectX11Api::Render()
  {
     // Clear the back buffer.
    d3d_context_->ClearRenderTargetView(render_target_view_, Vector4(0.0f, 1.0f, 0.0f, 1.0f).v);

    // Clear the depth buffer.
    d3d_context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    //do things in here ~~~~

    d3d_context_->IASetInputLayout(layout_);

    d3d_context_->PSSetShader(temp_pix_shader_, 0, 0);
    d3d_context_->VSSetShader(temp_vert_shader_, 0, 0);
    //SETTING MESH TO RENDER
    unsigned stride = sizeof(Vector4);
    unsigned offset = 0;
    d3d_context_->IASetVertexBuffers(0, 1, &temp_render_buffer_, &stride, &offset);
    int i = 0;
    d3d_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    d3d_context_->Draw(3, 0);

    
    d3d_swap_chain_->Present(0, 0);
  }

  void DirectX11Api::CleanUp()
  {

  }
}