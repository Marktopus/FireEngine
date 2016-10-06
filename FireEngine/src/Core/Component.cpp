#include "Precompiled.h"
#include "Component.h"

namespace Fire
{
  Component::Component() : active_(false)
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
}