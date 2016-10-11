#pragma once

namespace Fire
{ 
  class VertexBuffer;
  class Mesh
  {
    public:
      Mesh(const std::string& name, VertexBuffer* buf);
      Mesh(VertexBuffer* buf);
      ~Mesh();
      bool Load();
      bool Reload();
      std::string GetName();
      VertexBuffer* GetVertexBuffer();
    private:
      std::string name_;
      VertexBuffer* vert_buf_;
  };
}