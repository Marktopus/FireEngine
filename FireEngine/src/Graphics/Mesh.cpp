#include "Precompiled.h"
#include "Mesh.h"

namespace Fire
{
  Mesh::Mesh(const std::string& name, VertexBuffer* buf = nullptr)
  : name_(name),
    vert_buf_(buf)
  {

  }
    
  Mesh::Mesh(VertexBuffer* buf)
  : vert_buf_(buf)
  {

  }

  Mesh::~Mesh()
  {
    
  }

  bool Mesh::Load()
  {
    if(!name_.empty())
    {

    }
    //TODO: implement a mesh loader (obj/fbx/maya/anything)
    return false;
  }

  bool Mesh::Reload()
  {
    if(!name_.empty())
    {

    }
    //TODO: implement a mesh loader (obj/fbx/maya/anything)
    return false;
  }

  std::string Mesh::GetName()
  {
    return name_; 
  }

  VertexBuffer* Mesh::GetVertexBuffer()
  {
    return vert_buf_;
  }
}