#include "Precompiled.h"
#include "DxBuffers.h"
#include "DxIncludes.h"

#include "../Core/Engine.h"
#include "Graphics.h"
#include "DirectX11Api.h"
namespace Fire
{
  DxConstantBuffer::Element::Element(const char* name, size_t size, size_t offset)
  : name_(name),
    size_(size),
    offset_(offset)
  {
    
  }

  DxConstantBuffer::DxConstantBuffer(
    size_t size,
    size_t slot,
    void* src,
    CpuAccessType::Enum cpuAccess, 
    BufferUsageType::Enum bufferUsage) 
  : ConstantBuffer(size, src),
    slot_(slot)
  {
    Graphics* gSys = (Graphics*)Engine::GetEngine()->GetSystem(SystemType::Graphics);
    DirectX11Api* api = (DirectX11Api*)gSys->GetApi();
    ID3D11Device* device = api->GetDevice();

    D3D11_BUFFER_DESC bufferDesc;
    SecureZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
    D3D11_SUBRESOURCE_DATA* buffData = nullptr;

    bufferDesc.ByteWidth = size_;


    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    bufferDesc.CPUAccessFlags = 0;
    if( cpuAccess == CpuAccessType::Both ||
        cpuAccess == CpuAccessType::Read)
    {
      bufferDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
    } 
    if( cpuAccess == CpuAccessType::Both ||
        cpuAccess == CpuAccessType::Write)
    {
      bufferDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
    } 

    switch(bufferUsage)
    {
      case BufferUsageType::ReadCpuWriteGpu:
        bufferDesc.Usage = D3D11_USAGE_STAGING;
        break;
      case BufferUsageType::ReadGpu:
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        break;
      case BufferUsageType::ReadGpuWriteCpu:
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        break;
      case BufferUsageType::ReadWriteGpu:
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        break;
    }

    auto error = device->CreateBuffer(
      &bufferDesc,
      buffData,
      &buffer_);
    if(error != S_OK)
    {
      __debugbreak();
    }
  }


  DxConstantBuffer::~DxConstantBuffer()
  {
    buffer_->Release(); 
  }

  void DxConstantBuffer::Init()
  {
    // todo: delete
  }

  void DxConstantBuffer::BufferData(void* tempSrc)
  { 
    void* src = (tempSrc) ? tempSrc : source_;
    if (!source_)
    {
      source_ = src;
    }
    if(src)
    {
      // directx call
      Graphics* gSys = (Graphics*)Engine::GetEngine()->GetSystem(SystemType::Graphics);
      DirectX11Api* api = (DirectX11Api*)gSys->GetApi();
      ID3D11DeviceContext* context = api->GetDeviceContext();
      D3D11_MAPPED_SUBRESOURCE mapped;
      auto err = context->Map(
        buffer_, 
        0, 
        D3D11_MAP_WRITE_DISCARD, 
        0, 
        &mapped);
      if (err != S_OK)
      {
        //panic
        __debugbreak();
      }
      memcpy(mapped.pData, src, size_);

      context->Unmap(buffer_, 0);
    }
  }


  void* DxConstantBuffer::GetBufferPointer()
  {
    return buffer_;
  }

  size_t DxConstantBuffer::GetSlot()
  {
    return slot_;
  }
  

  DxVertexBuffer::DxVertexBuffer(
    size_t size, 
    size_t stride, 
    void* src,
    CpuAccessType::Enum cpuAccess,
    BufferUsageType::Enum bufferUsage)
  : VertexBuffer(size, stride, src)
  {
    Graphics* gSys = (Graphics*)Engine::GetEngine()->GetSystem(SystemType::Graphics);
    DirectX11Api* api = (DirectX11Api*)gSys->GetApi();
    ID3D11Device* device = api->GetDevice();
    D3D11_BUFFER_DESC bufferDesc;
    SecureZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
    D3D11_SUBRESOURCE_DATA* buffData = nullptr;

    bufferDesc.ByteWidth = size_;

    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffData = (D3D11_SUBRESOURCE_DATA*) alloca(sizeof(D3D11_SUBRESOURCE_DATA));
    SecureZeroMemory(buffData, sizeof(D3D11_SUBRESOURCE_DATA));
    buffData->pSysMem = source_;

    bufferDesc.CPUAccessFlags = 0;
    if( cpuAccess == CpuAccessType::Both ||
        cpuAccess == CpuAccessType::Read)
    {
      bufferDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
    } 
    if( cpuAccess == CpuAccessType::Both ||
        cpuAccess == CpuAccessType::Write)
    {
      bufferDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
    } 

    switch(bufferUsage)
    {
      case BufferUsageType::ReadCpuWriteGpu:
        bufferDesc.Usage = D3D11_USAGE_STAGING;
        break;
      case BufferUsageType::ReadGpu:
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        break;
      case BufferUsageType::ReadGpuWriteCpu:
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        break;
      case BufferUsageType::ReadWriteGpu:
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        break;
    }

    auto error = device->CreateBuffer(
      &bufferDesc,
      buffData,
      &buffer_);
    if(error != S_OK)
    {
      __debugbreak();
    }
  } 
  DxVertexBuffer::~DxVertexBuffer()
  {
    buffer_->Release(); 
  }

  void DxVertexBuffer::Init()
  {
    // todo: delete
  }

  void DxVertexBuffer::SetSource(void* src)
  {
    // do a bunch of dx shit.....

  }

  void* DxVertexBuffer::GetBufferPointer()
  {
    return buffer_;
  }  

}