#pragma once

#include "SystemType.h"
namespace Fire 
{
  class System;
  class FrameCounter;
  class Engine 
  {
    public:
      Engine();
      ~Engine();

      static void Activate();
      static void Deactivate();
      static bool GetActive();

      static System* GetSystem(SystemType::Enum type);
      static void AddSystem(System* system);
      static void Load();
      static void Initialize();
      static void Reinitialize();
      static void Update();
      static void CleanUp();
      static Engine* GetEngine();
    private:
      static Engine* engine;
      FrameCounter* frame_counter_;
      bool active_;
      System* systems_[SystemType::Count];
  };
}

