#include "Precompiled.h"

#include "System.h"
#include "Component.h"


namespace Fire
{
  System::System(SystemType::Enum type )
  : active_(false),
    type_(type)
  {

  }

  System::~System()
  {

  }
  
  void System::Activate()
  {
    for(auto cit : components_)
    {
      cit->Deactivate();
    }
    active_ = true;
  }

  void System::Deactivate()
  {
    for(auto cit : components_)
    {
      cit->Deactivate();
    }
    active_ = false;
  }

  bool System::GetActive()
  {
    return active_;
  }

  SystemType::Enum System::GetType()
  {
    return type_;
  }

  void System::AddComponent(Component* comp)
  {
    components_.push_back(comp);
  }
}
