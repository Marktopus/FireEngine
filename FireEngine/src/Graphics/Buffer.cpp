#include "Precompiled.h"
#include "Buffer.h"

namespace Fire
{
  
  ConstantBuffer::ConstantBuffer(
    size_t size, 
    void* src)
  : size_(size),
    source_(src),
    needs_update_(true)
  { 

  }

  ConstantBuffer::~ConstantBuffer()
  {

  }

  void ConstantBuffer::SetSource(void* src)
  {
    needs_update_ = true;
    source_ = src;
  }

  void* ConstantBuffer::GetSource()
  {
    return source_;
  }

  size_t ConstantBuffer::GetSize()
  {
    return size_;
  }

  bool ConstantBuffer::NeedsUpdate()
  { 
    return true;
    return needs_update_;
  }

  void ConstantBuffer::Update(void* tempSrc)
  {
    this->BufferData(tempSrc);
    needs_update_ = false;
  }

  void ConstantBuffer::AddElement(Element* element)
  {
    elements_.insert(std::make_pair(element->name_, element));
  }

  void ConstantBuffer::AddElement(const char* name, size_t size, size_t offset)
  {
    AddElement(new Element(name, size, offset));
  }

  void ConstantBuffer::WriteElement(const char* name, void* source)
  {
    auto elit = elements_.find(name);
    if(elit != elements_.end())
    {
      Element* el = elit->second;
      memcpy((char*)source_ + el->offset_, source, el->size_);
    }
    needs_update_ = true;
  }

  void ConstantBuffer::WriteBuffer(void* source)
  {
    memcpy(source_, source, size_);
    needs_update_ = true;
  }
  
  VertexBuffer::VertexBuffer(
    size_t size, 
    size_t stride, 
    void* src)
  : size_(size),
    stride_(stride),
    source_(src),
    num_verts_(size / stride)
  {

  }

  VertexBuffer::~VertexBuffer()
  {

  }

  void* VertexBuffer::GetSource()
  {
    return source_;
  }
  size_t VertexBuffer::GetSize()
  {
    return size_;
  }
  size_t VertexBuffer::GetStride()
  {
    return stride_;
  }
  size_t VertexBuffer::GetNumVerts()
  {
    return num_verts_;
  }
}