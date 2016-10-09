#include "Precompiled.h"
#include "DxBuffers.h"
#include "DxIncludes.h"
namespace Fire
{
  DxVertexBuffer::DxVertexBuffer(ID3D11Device* device, BufferType::Enum type, size_t size, void* src) : ConstantBuffer(type, size, src)
  {
    D3D11_BUFFER_DESC bufferDesc;
    SecureZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
    D3D11_SUBRESOURCE_DATA* buffData = nullptr;

    bufferDesc.ByteWidth = size_;

    switch(type)
    {
      case BufferType::Vertex:

        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        buffData = (D3D11_SUBRESOURCE_DATA*) alloca(sizeof(D3D11_SUBRESOURCE_DATA));
        SecureZeroMemory(buffData, sizeof(D3D11_SUBRESOURCE_DATA));
        buffData->pSysMem = source_;
        break;
      case BufferType::Constant:
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        break;
    }
    //todo: add flag for cpu access and gpu access
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;

    auto error = device->CreateBuffer(
      &bufferDesc,
      buffData,
      &buffer_);
    if(error != S_OK)
    {
      __debugbreak();
    }
  } 
}