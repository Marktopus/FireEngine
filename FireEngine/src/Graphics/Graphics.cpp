#include "Precompiled.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"


#include "Graphics.h"
#include "Math/Matrix4.h"
#include "Core/Engine.h"
#include "DirectX11Api.h"
namespace Fire
{
  Graphics::Graphics()
  {
    api_ = new DirectX11Api();
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

    api_->Render();
  }

  void Graphics::Reinitialize()
  {

  }

  void Graphics::CleanUp()
  {
    window_->close();
  }
}