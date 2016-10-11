#pragma once

#include "Shader.h"

struct ID3D11Device;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
namespace Fire
{
  class DxShader : public Shader
  {
    public:
      DxShader(const std::string& name);
      ~DxShader();
      // idea - default shader that tells you your shits wrong
      bool Compile(void* device);
      bool AttemptRecompile(void* device);

      void* GetVertPointer();
      void* GetPixPointer();
      void* GetLayoutPointer();
    private:
      
      ID3D11VertexShader* vert_shader_;
      ID3D11PixelShader*  pix_shader_;
      ID3D11InputLayout*  layout_;
  };  
}
