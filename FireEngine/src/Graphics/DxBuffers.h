#pragma once
#include "Buffer.h"

struct ID3D11Buffer;
struct ID3D11Device;
namespace Fire
{
  class DxConstantBuffer : public ConstantBuffer
  {
    public:
      DxConstantBuffer(
        ID3D11Device* device, 
        size_t size,
        void* src = nullptr,
        CpuAccessType::Enum cpuAccess = CpuAccessType::Write, 
        BufferUsageType::Enum bufferUsage = BufferUsageType::ReadGpuWriteCpu);
      ~DxConstantBuffer();

      void Init() override;
      void SetSource(void* src) override;
      void* GetBufferPointer() override;
    private:
      ID3D11Buffer* buffer_;
  };

  class DxVertexBuffer : public VertexBuffer
  {
    public:
      DxVertexBuffer(
        ID3D11Device* device, 
        size_t size, 
        size_t stride, 
        void* src = nullptr,
        CpuAccessType::Enum cpuAccess = CpuAccessType::None,
        BufferUsageType::Enum bufferUsage = BufferUsageType::ReadWriteGpu);
      ~DxVertexBuffer();

      void Init() override;
      void SetSource(void* src) override;
      void* GetBufferPointer() override;
    private:
      ID3D11Buffer* buffer_;
      unsigned stride_;
  };
}