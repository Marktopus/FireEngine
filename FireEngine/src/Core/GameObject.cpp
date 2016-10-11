#include "Precompiled.h"
#include "GameObject.h"
#include "Component.h"

namespace Fire
{
  GameObject::GameObject()
  {
    
  }

  GameObject::~GameObject()
  {

  }

  void GameObject::AddComponent(Component* newComp)
  { 
    ComponentType::Enum type = newComp->GetType();
    if(!components_[type])
    {
      components_[type] = newComp;
    }
  }

  Component* GameObject::GetComponent(ComponentType::Enum compType)
  {
    return components_[compType];
  }
}