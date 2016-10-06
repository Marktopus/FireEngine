#include "Precompiled.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"


#include "Graphics.h"
#include "Math/Matrix4.h"
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
    Matrix4 one(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0);
    Matrix4 two(17.0,18.0,19.0,20.0,21.0,22.0,23.0,24.0,25.0,26.0,27.0,28.0,29.0,30.0,31.0,32.0);
    //one.Identity();
    //two.Identity();

    Matrix4 three = one * two;
    
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