#include "Precompiled.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"


#include "Graphics.h"
#include "Core/Engine.h"
namespace Fire
{
  Graphics::Graphics()
  {

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
  }

  void Graphics::Reinitialize()
  {

  }

  void Graphics::CleanUp()
  {
    window_->close();
  }
}