#include "Precompiled.h"
#include "DxBuffers.h"
#include "DxIncludes.h"
namespace Fire
{
  DxConstantBuffer::DxConstantBuffer(
    ID3D11Device* device, 
    size_t size,
    void* src,
    CpuAccessType::Enum cpuAccess, 
    BufferUsageType::Enum bufferUsage) 
  : ConstantBuffer(size, src)
  {
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

  void DxConstantBuffer::SetSource(void* src)
  {
    // do a bunch of dx shit.....

  }

  void* DxConstantBuffer::GetBufferPointer()
  {
    return buffer_;
  }

  DxVertexBuffer::DxVertexBuffer(
    ID3D11Device* device, 
    size_t size, 
    size_t stride, 
    void* src,
    CpuAccessType::Enum cpuAccess,
    BufferUsageType::Enum bufferUsage)
  : VertexBuffer(size, stride, src)
  {
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