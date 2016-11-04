#include "Precompiled.h"
#include "Shader.h"
namespace Fire
{
  Shader::Shader(const std::string& name)
  : shader_name_(name)
  {
  
  }

  Shader::~Shader()
  {

  }
  ConstantBuffer* Shader::GetBuffer(const char* name)
  {
    auto bufIt = constant_buffers_.find(name);
    if(bufIt != constant_buffers_.end())
    { 
      return bufIt->second;
    }
    return nullptr;
  }
}