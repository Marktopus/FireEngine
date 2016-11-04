#include "Precompiled.h"
#include "GameObject.h"
#include "Component.h"

namespace Fire
{
  GameObject::GameObject()
  : scale_(1.0f, 1.0f, 1.0f)
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
      components_[type]->base_ = this;
    }
  }

  Component* GameObject::GetComponent(ComponentType::Enum compType)
  {
    return components_[compType];
  }

  Vector3 GameObject::GetPosition()
  {
    return position_;
  }

  Vector3 GameObject::GetScale()
  {
    return scale_;
  }

  Vector3 GameObject::GetRotation()
  {
    return rotation_;
  }
}