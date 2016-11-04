#pragma once

#include "ComponentType.h"

namespace Fire 
{
  class GameObject;
  class Component
  {
    public:
      Component(ComponentType::Enum type);
      virtual ~Component();

      void Activate();
      void Deactivate();
      bool GetActive();
      ComponentType::Enum GetType();
      GameObject* GetBase();
      

      virtual void Initialize() = 0;
      virtual void Reinitialize() = 0;
      virtual void Load() = 0;
      virtual void Update(float dt) = 0;
    protected:
      friend class GameObject;
      ComponentType::Enum type_;
      bool active_;
      GameObject* base_;
  };
}