#pragma once

namespace Fire
{
  class Component;
  class Engine;
  class System
  {
    public:
      System();
      virtual ~System();

      virtual void Activate() final;
      virtual void Deactivate() final;
      virtual bool GetActive() final;
      virtual void AddComponent(Component* system) final;
      virtual void SetEngine(Engine* engine) final;

      virtual void Load() = 0;
      virtual void Initialize() = 0;
      virtual void Reinitialize() = 0;
      virtual void Update(float dt) = 0;
      virtual void CleanUp() = 0;

    protected:
      Engine* engine_;

    private:
      std::vector<Component*> components_;
      bool active_;
  };
}
