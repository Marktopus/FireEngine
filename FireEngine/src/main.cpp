#include "Precompiled.h"
#include "Core/Engine.h"
#include "Graphics/Graphics.h"
int main()
{
  Fire::Engine* engine = new Fire::Engine();
  engine->AddSystem(new Fire::Graphics());
  engine->Load();
  engine->Initialize();

  engine->Activate();

  while(engine->GetActive())
  {
    engine->Update(1.0/60.0);
  }

  engine->CleanUp();
}

