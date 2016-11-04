#include "Precompiled.h"
#include "DxShader.h"
#include "DxIncludes.h"
#include "DxBuffers.h"

#include "../Core/Engine.h"
#include "Graphics.h"
#include "DirectX11Api.h"
namespace Fire
{
  DxShader::DxShader(const std::string& name)
  : Shader(name)
  {

  }
  
  DxShader::~DxShader()
  {

  }

  bool DxShader::Compile(void* info)
  {
    ID3D11Device* device = (ID3D11Device*)info;
    ID3D10Blob* errorMsg; 
    ID3D10Blob* vertShaderBuf; 
    std::string filePath = "src/shaders/";
    std::string vertShaderName = filePath + shader_name_ + ".vs";
    std::wstring dxName(vertShaderName.begin(), vertShaderName.end());
    auto error = D3DCompileFromFile(
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
      std::cout << "shader " << vertShaderName << "failed to compile with error" << (char*)errorMsg->GetBufferPointer() << std::endl;
      errorMsg->Release();
      return false;
    }
    error = device->CreateVertexShader(
      vertShaderBuf->GetBufferPointer(), 
      vertShaderBuf->GetBufferSize(), 
      nullptr, 
      &vert_shader_);  
    if(error)
    {
      __debugbreak();
      return false;
    }


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







    for(size_t i = 0; i < shaderDesc.ConstantBuffers; i++)
    {
      ID3D11ShaderReflectionConstantBuffer* pConstantReflection = vertShaderReflection->GetConstantBufferByIndex(i);
      D3D11_SHADER_BUFFER_DESC desc;
      error = pConstantReflection->GetDesc(&desc);
      if(error != S_OK)
      {
        __debugbreak();
      }

      DxConstantBuffer* newBuf = new DxConstantBuffer(
        desc.Size,
        i
      );

      for(size_t varInd = 0; varInd < desc.Variables; ++varInd)
      {
        ID3D11ShaderReflectionVariable* curVar = pConstantReflection->GetVariableByIndex(varInd);
        D3D11_SHADER_VARIABLE_DESC varDesc;
        error = curVar->GetDesc(&varDesc);
        if(error != S_OK)
        {
          __debugbreak();
        }

        newBuf->AddElement(varDesc.Name, varDesc.Size, varDesc.StartOffset);
      }

      constant_buffers_.insert(std::make_pair(desc.Name, newBuf));
    }

    error = device->CreateInputLayout(
      &inputLayoutDesc[0],
      inputLayoutDesc.size(),
      vertShaderBuf->GetBufferPointer(),
      vertShaderBuf->GetBufferSize(),
      &layout_);

    if(error)
    {
      __debugbreak();
    }

    std::string pixShaderName = filePath + shader_name_ + ".ps";
    ID3D10Blob* pixShaderBuf; 

    dxName.assign(pixShaderName.begin(), pixShaderName.end());
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
      std::cout << "shader " << pixShaderName << "failed to compile with error" << (char*) errorMsg->GetBufferPointer() << std::endl;
      errorMsg->Release();
      return false;
    }
    error = device->CreatePixelShader(
      pixShaderBuf->GetBufferPointer(),
      pixShaderBuf->GetBufferSize(),
      nullptr,
      &pix_shader_);
    if(error)
    {
      __debugbreak();
      return false;
    }

    return true;
  }

  bool DxShader::AttemptRecompile(void* info)
  {
    return false;
  }

  void DxShader::PreRender()
  {
    UpdateBuffers();
  }

  void DxShader::UpdateBuffer(const char* name, void* tempSrc)
  {
    ID3D11Buffer* dxBuf;
    auto bufIt = constant_buffers_.find(name);
    if (bufIt != constant_buffers_.end())
    {
      DxConstantBuffer* buf = (DxConstantBuffer*)bufIt->second;
      
      if (buf->NeedsUpdate())
      {
        buf->Update(tempSrc);
      }
      dxBuf = (ID3D11Buffer*)buf->GetBufferPointer();
      Graphics* gSys = (Graphics*)Engine::GetEngine()->GetSystem(SystemType::Graphics);
      DirectX11Api* api = (DirectX11Api*)gSys->GetApi();
      ID3D11DeviceContext* context = api->GetDeviceContext();
      context->VSSetConstantBuffers(/*0,/*/buf->GetSlot(),/**/ 1, &dxBuf);  
      //context->VSSetConstantBuffers(buf->GetSlot(), 1, &dxBuf);  
    }
  }

  void DxShader::UpdateBuffers()
  {
    std::vector<ID3D11Buffer*> bufArray;
    bufArray.resize(constant_buffers_.size());
    DxConstantBuffer* buf;

    int iteri = 0;
    for(auto it : constant_buffers_)
    { 
      buf = (DxConstantBuffer*)it.second;
      bufArray[buf->GetSlot()] = (ID3D11Buffer*)buf->GetBufferPointer();
      if (buf->NeedsUpdate())
      {
        buf->Update();
      }
    }

    Graphics* gSys = (Graphics*)Engine::GetEngine()->GetSystem(SystemType::Graphics);
    DirectX11Api* api = (DirectX11Api*)gSys->GetApi();
    ID3D11DeviceContext* context = api->GetDeviceContext();
    context->VSSetConstantBuffers(0, constant_buffers_.size(), &bufArray[0]);
  }

  void* DxShader::GetVertPointer()
  {
    return vert_shader_;
  }

  void* DxShader::GetPixPointer()
  {
    return pix_shader_;
  }

  void* DxShader::GetLayoutPointer()
  {
    return layout_;
  }
}