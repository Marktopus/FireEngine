#pragma once

namespace Fire
{
  namespace CpuAccessType
  {
    enum Enum
    {
      None,
      Read,
      Write,
      Both
    };
  }
  namespace BufferUsageType
  {
    enum Enum
    {
      ReadWriteGpu,
      ReadGpu,
      ReadGpuWriteCpu,
      ReadCpuWriteGpu
    };
  }
  class ConstantBuffer
  {
    public:
      ConstantBuffer(
        size_t size, 
        void* src = nullptr,  
        CpuAccessType::Enum cpuAccess = CpuAccessType::Write, 
        BufferUsageType::Enum bufferType = BufferUsageType::ReadGpuWriteCpu);
      virtual ~ConstantBuffer();
      virtual void Init() = 0;
      virtual void BufferData() = 0;
      virtual void SetSource(void* src) = 0;
      virtual void* GetBufferPointer() = 0;
    protected:
      size_t size_;
      void* source_;
  };

  class VertexBuffer
  {
    public:
      VertexBuffer(
        size_t size, 
        size_t stride, 
        void* src = nullptr,  
        CpuAccessType::Enum cpuAccess = CpuAccessType::None, 
        BufferUsageType::Enum bufferType = BufferUsageType::ReadGpu);
      virtual ~VertexBuffer();
      virtual void Init() = 0;
      virtual void* GetBufferPointer() = 0;
    protected:
      size_t size_;
      size_t stride_;
  };
}
