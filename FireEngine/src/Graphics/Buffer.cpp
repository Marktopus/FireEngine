#include "Precompiled.h"
#include "Buffer.h"

namespace Fire
{
  
  ConstantBuffer::ConstantBuffer(
    size_t size, 
    void* src)
  : size_(size),
    source_(src)
  { 

  }

  ConstantBuffer::~ConstantBuffer()
  {

  }

  void* ConstantBuffer::GetSource()
  {
    return source_;
  }

  size_t ConstantBuffer::GetSize()
  {
    return size_;
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