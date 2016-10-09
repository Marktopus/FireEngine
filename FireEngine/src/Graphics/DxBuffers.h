#pragma once
#include "Buffer.h"

struct ID3D11Buffer;
struct ID3D11Device;
namespace Fire
{
  class DxVertexBuffer : public ConstantBuffer
  {
    public:
      DxVertexBuffer(ID3D11Device* device, BufferType::Enum type, size_t size, void* src = nullptr);
      DxVertexBuffer();
      ~DxVertexBuffer();

      void Init() override;
      void SetSource(void* src) override;
      void* GetBufferPointer() override;
    private:
      ID3D11Buffer* buffer_;
      unsigned stride;
  };
  class DxConstantBuffer : public ConstantBuffer
  {
    public:
      DxConstantBuffer(ID3D11Device* device, BufferType::Enum type, size_t size, void* src = nullptr);
      DxConstantBuffer();
      ~DxConstantBuffer();

      void Init() override;
      void SetSource(void* src) override;
      void* GetBufferPointer() override;
    private:
      ID3D11Buffer* buffer_;
  };
    p
}