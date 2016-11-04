#include "Precompiled.h"
#include "Component.h"

namespace Fire
{
  Component::Component(ComponentType::Enum type) 
  : active_(false),
    type_(type)
  {

  }

  Component::~Component()
  {

  }

  void Component::Activate()
  {
    active_ = true;
  }

  void Component::Deactivate()
  {
    active_ = false;
  }

  bool Component::GetActive()
  {
    return active_;
  }

  ComponentType::Enum Component::GetType()
  {
    return type_;
  }

  GameObject* Component::GetBase()
  {
    return base_;
  }
}