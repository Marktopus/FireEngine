#pragma once

namespace Fire 
{
  class Component
  {
    public:
      Component();
      virtual ~Component();

      virtual void Activate() final;
      virtual void Deactivate() final;
      virtual bool GetActive() final;

      virtual void Initialize() = 0;
      virtual void Reinitialize() = 0;
      virtual void Load() = 0;
      virtual void Update(float dt) = 0;
    private:
      bool active_;
  };
}