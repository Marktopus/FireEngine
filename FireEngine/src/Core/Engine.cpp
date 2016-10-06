#include "Precompiled.h"

#include "Engine.h"
#include "System.h"

#include "Core/FrameCounter.h"

namespace Fire
{
  Engine::Engine() 
  : active_(false),
    frame_counter_(nullptr)
  {
    
  }

  Engine::~Engine()
  {

  }

  void Engine::AddSystem(System* system) 
  {
    system->SetEngine(this);
    systems_.push_back(system);
  }

  void Engine::Load()
  {
    for(auto sit : systems_)
    {
      sit->Load();
    }
  }

  void Engine::Initialize()
  {
    frame_counter_ = new FrameCounter();
    for(auto sit : systems_)
    {
      sit->Initialize();
    }
  }

  void Engine::Reinitialize()
  {
    for(auto sit : systems_)
    {
      sit->CleanUp();
      sit->Initialize();
    }
  }

  void Engine::Update()
  {
    frame_counter_->Update();
    for(auto sit : systems_)
    {
      sit->Update(frame_counter_->GetDt());
    }
  }

  void Engine::CleanUp()
  {
    for(auto sit : systems_)
    {
      sit->CleanUp();
    }
  }

  void Engine::Activate()
  {
    for(auto sit : systems_)
    {
      sit->Activate();
    }
    active_ = true;
  }

  void Engine::Deactivate()
  {
    for(auto sit : systems_)
    {
      sit->Deactivate();
    }
    active_ = false;
  }

  bool Engine::GetActive()
  {
    return active_;
  }
}