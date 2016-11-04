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
        size_t size,
        size_t slot,
        void* src = nullptr,
        CpuAccessType::Enum cpuAccess = CpuAccessType::Write, 
        BufferUsageType::Enum bufferUsage = BufferUsageType::ReadGpuWriteCpu);
      ~DxConstantBuffer();

      void Init() override;
      void BufferData(void* tempSrc = nullptr);
      void* GetBufferPointer() override;
      size_t GetSlot();
    private:
      size_t slot_;
      ID3D11Buffer* buffer_;
  };

  class DxVertexBuffer : public VertexBuffer
  {
    public:
      DxVertexBuffer(
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