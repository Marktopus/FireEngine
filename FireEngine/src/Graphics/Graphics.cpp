#include "Precompiled.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"


#include "Graphics.h"
#include "Math/Matrix4.h"
#include "Core/Engine.h"
#include "DirectX11Api.h"
#include "Mesh.h"
#include "Shader.h"
#include "Components/Renderable.h"
#include "Buffer.h"
#include "Camera.h"
#include "Core/GameObject.h"
namespace Fire
{
  Graphics::Graphics()
  : cur_buf_(nullptr),
    cur_texture_(nullptr),
    cur_shader_(nullptr),
    System(SystemType::Graphics)

  {
    api_ = new DirectX11Api();
    camera_ = new Camera();
  }

  Graphics::~Graphics()
  {

  }

  void Graphics::Load()
  {
    
  }

  void Graphics::Initialize()
  {
    window_ = new sf::Window(sf::VideoMode(800, 600), "Fire Engine");
    api_->Initialize(window_);
    //   BUFFER INIT
    Vector4* vertices = new Vector4[3];
    vertices[0] = Vector4(-0.5, -0.5, 0.0, 1.0);
    vertices[1] = Vector4(0.5, -0.5, 0.0, 1.0);
    vertices[2] = Vector4(0.5, 0.5, 0.0, 1.0);
    VertexBuffer* newBuf = api_->MakeVertexBuffer(
      sizeof(Vector4) * 3,
      sizeof(Vector4),
      vertices);
    
    meshes_.insert(std::make_pair("triangle", new Mesh(newBuf)));
    Shader* newShader = api_->MakeShader("color");
    shaders_.insert(std::make_pair("color", newShader));
    
    camera_->UpdatePerspective(); 
    newShader->UpdateBuffer("perspBuf", &camera_->perspective_);

    camera_->UpdateView(); 
    newShader->UpdateBuffer("viewBuf",&camera_->view_);

    renderables_.push_back(new Renderable("triangle", "color"));
  }

  void Graphics::Update(float dt)
  {
    if(window_->isOpen())
    { 
      sf::Event sfevent;
      while(window_->pollEvent(sfevent))
      {
        if(sfevent.type == sf::Event::Closed)
        {
          engine_->Deactivate();
        }
      }
    }
    api_->BeginScene();
    for(auto it : renderables_)
    {
      it->PrepForRender();
      GameObject* base = it->GetBase();
      Matrix4 transformation;
      transformation.Identity();
      Vector3 pos;
      pos.Zero();
      //pos.x += 0.05;
      Vector3 rot;
      rot.Zero();
      rot.z = Math::Pi/4.0f;
      transformation.Translate(pos);//base->GetPosition());
      transformation.Rotate(rot);//base->GetRotation());
      transformation.Scale(Vector3(1.0f,1.0f,1.0f));//base->GetScale());
      //transformation.Transpose();


      cur_shader_->UpdateBuffer("modelBuf",&transformation);
      
      api_->Render(cur_buf_->GetNumVerts());
    }
    api_->EndScene();
  }

  void Graphics::Reinitialize()
  {

  }

  void Graphics::CleanUp()
  {
    window_->close();
  }
    
  GraphicsApi* Graphics::GetApi()
  {
    return api_;
  }

  void Graphics::SetMesh(const std::string& meshName)
  { 
    auto mesh = meshes_.find(meshName);
    if(mesh != meshes_.end())
    { 
      VertexBuffer* buf = (*mesh).second->GetVertexBuffer();
      if(buf != cur_buf_)
      {
        cur_buf_ = buf;
        api_->SetMesh(buf);
      }
    }
  }

  void Graphics::SetTexture(const std::string& textureName)
  {
    auto textureit = textures_.find(textureName);
    if(textureit != textures_.end())
    { 
      Texture* texture = textureit->second;
      // todo: make texture interface, grab specific texture here
      if(texture != cur_texture_)
      {
        cur_texture_ = texture;
        api_->SetTexture();
      }
    }
  }

  void Graphics::SetShader(const std::string& shaderName)
  {
    auto shaderit = shaders_.find(shaderName);
    if(shaderit != shaders_.end())
    { 
      Shader* shader = shaderit->second;
      if(shader != cur_shader_)
      {
        cur_shader_ = shader;
        shader->UpdateBuffers();
        api_->SetShader(shader);
      }
      shader->PreRender();
    }
  }

}