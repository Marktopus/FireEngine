#pragma once

namespace Fire
{
  class ConstantBuffer;
  class Shader
  {
    public:
      Shader(const std::string& name);
      virtual ~Shader();

      virtual bool Compile(void* info) = 0;
      virtual bool AttemptRecompile(void* info) = 0;

      virtual void* GetVertPointer() = 0;
      virtual void* GetPixPointer() = 0;
      virtual void* GetLayoutPointer() = 0;
    protected:
      std::string shader_name_;
      std::string shader_source_;
      std::vector<ConstantBuffer*> constant_buffers_;
  };
}
