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
      struct Element 
      {
        Element(const char* name, size_t size, size_t offset);
        const char* name_;
        size_t size_;
        size_t offset_;
      };
      ConstantBuffer(
        size_t size, 
        void* src = nullptr);
      virtual ~ConstantBuffer();
      virtual void Init() = 0;
      virtual void BufferData(void* tempSrc = nullptr) = 0;
      virtual void SetSource(void* src);
      virtual void* GetSource();
      virtual size_t GetSize();
      virtual void* GetBufferPointer() = 0;

      bool NeedsUpdate();
      void Update(void* tempSrc = nullptr);

      void AddElement(Element* element);
      void AddElement(const char* name, size_t size, size_t offset);
      void WriteElement(const char* name, void* source);
      void WriteBuffer(void* source);
    protected:
      size_t size_;
      void* source_;
      bool needs_update_;
      std::unordered_map<const char*, Element*> elements_;
  };

  class VertexBuffer
  {
    public:
      VertexBuffer(
        size_t size, 
        size_t stride, 
        void* src = nullptr);
      virtual ~VertexBuffer();
      virtual void Init() = 0;
      virtual void SetSource(void* src) = 0;
      virtual void* GetSource();
      virtual size_t GetSize();
      virtual size_t GetStride();
      virtual size_t GetNumVerts();
      virtual void* GetBufferPointer() = 0;
    protected:
      void*  source_;
      size_t size_;
      size_t stride_;
      size_t num_verts_;
  };
}
