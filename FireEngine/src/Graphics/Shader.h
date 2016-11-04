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
      virtual void PreRender() = 0;
      ConstantBuffer* GetBuffer(const char* name);
      virtual void UpdateBuffers() = 0;
      virtual void UpdateBuffer(const char* name, void* tempSrc = nullptr) = 0;

      virtual void* GetVertPointer() = 0;
      virtual void* GetPixPointer() = 0;
      virtual void* GetLayoutPointer() = 0;

    protected:
      std::string shader_name_;
      std::string shader_source_;
      std::unordered_map<std::string, ConstantBuffer*> constant_buffers_;
  };
}
