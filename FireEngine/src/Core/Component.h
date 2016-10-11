#pragma once

#include "ComponentType.h"

namespace Fire 
{
  class Component
  {
    public:
      Component(ComponentType::Enum type);
      virtual ~Component();

      void Activate();
      void Deactivate();
      bool GetActive();
      ComponentType::Enum GetType();
      

      virtual void Initialize() = 0;
      virtual void Reinitialize() = 0;
      virtual void Load() = 0;
      virtual void Update(float dt) = 0;
    protected:
      ComponentType::Enum type_;
      bool active_;
  };
}