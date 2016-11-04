#pragma once
#include "SystemType.h"
namespace Fire
{
  class Component;
  class Engine;
  class System
  {
    public:
      System(SystemType::Enum type = SystemType::Count);
      virtual ~System();

      void Activate();
      void Deactivate();
      bool GetActive();
      SystemType::Enum GetType();
      void AddComponent(Component* system);

      virtual void Load() = 0;
      virtual void Initialize() = 0;
      virtual void Reinitialize() = 0;
      virtual void Update(float dt) = 0;
      virtual void CleanUp() = 0;

    protected:
      Engine* engine_;
      SystemType::Enum type_;
      std::vector<Component*> components_;
      bool active_;
  };
}
