#include "Precompiled.h"
#include "Buffer.h"

namespace Fire
{
  ConstantBuffer::ConstantBuffer(BufferType::Enum type, size_t size, void* src = nullptr)
  : type_(type),
    size_(size),
    source_(src)
  {
    
  }

  ConstantBuffer::~ConstantBuffer()
  {

  }
}