#pragma once

#include "ComponentType.h"
#include "Math/Vector3.h"
namespace Fire
{
  class Component;
  class GameObject
  {
    public:
      GameObject();
      ~GameObject();

      void AddComponent(Component* newComp);
      Component* GetComponent(ComponentType::Enum compType);
    private:
      std::string name_;
      Vector3 position_;
      Vector3 scale_;
      Vector3 rotation_;
      Component* components_[ComponentType::Count];
  };

}