#pragma once
#include <vector>

namespace Fire 
{
  class System;
  class FrameCounter;
  class Engine 
  {
    public:
      Engine();
      ~Engine();

      virtual void Activate() final;
      virtual void Deactivate() final;
      virtual bool GetActive() final;

      void AddSystem(System* system);
      void Load();
      void Initialize();
      void Reinitialize();
      void Update(float dt);
      void CleanUp();
    private:
      FrameCounter* timer_;
      bool active_;
      std::vector<System*> systems_;
  };
}

