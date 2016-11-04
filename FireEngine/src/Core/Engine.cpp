#include "Precompiled.h"

#include "Engine.h"
#include "System.h"

#include "Core/FrameCounter.h"

Fire::Engine* Fire::Engine::engine = new Fire::Engine();
namespace Fire
{
  Engine::Engine() 
  : active_(false),
    frame_counter_(nullptr)
  {
    memset(systems_, 0, sizeof(System*) * SystemType::Count);
  }

  Engine::~Engine()
  {

  }

  System* Engine::GetSystem(SystemType::Enum type)
  {
    return engine->systems_[type];
  }

  void Engine::AddSystem(System* system) 
  { 
    SystemType::Enum type = system->GetType();
    if(engine->systems_[type] == nullptr)
    {
      engine->systems_[type] = system;
    }
  }

  void Engine::Load()
  {
    for(auto sit : engine->systems_)
    {
      if(sit)
      {
        sit->Load();
      }
    }
  }

  void Engine::Initialize()
  {
    engine->frame_counter_ = new FrameCounter();
    for(auto sit : engine->systems_)
    {
      if(sit)
      {
        sit->Initialize();
      }
    }
  }

  void Engine::Reinitialize()
  {
    for(auto sit : engine->systems_)
    {
      if(sit)
      {
        sit->CleanUp();
        sit->Initialize();
      }
    }
  }

  void Engine::Update()
  {
    engine->frame_counter_->Update();
    for(auto sit : engine->systems_)
    {
      if(sit)
      {
        sit->Update(engine->frame_counter_->GetDt());
      }
    }
  }

  void Engine::CleanUp()
  {
    for(auto sit : engine->systems_)
    {
      if(sit)
      {
        sit->CleanUp();
      }
    }
  }

  void Engine::Activate()
  { 
    for(auto sit : engine->systems_)
    {
      if(sit)
      {
        sit->Activate();
      }
    }
    engine->active_ = true;
  }

  void Engine::Deactivate()
  {
    for(auto sit : engine->systems_)
    {
      if(sit)
      {
        sit->Deactivate();
      }
    }
    engine->active_ = false;
  }

  bool Engine::GetActive()
  {
    return engine->active_;
  }

  Engine* Engine::GetEngine()
  {
    return Engine::engine;
  }
}
