#pragma once

#include "SDL3/SDL_video.h"
#include "foundation/ecs/entityManager.h"
#include "foundation/ecs/systemManager.h"

class UISystem : public BaseSystem {
public:
  Entity selectedEntity = -1;

  UISystem(SDL_Window *w, SDL_GLContext gl);

  void beginFrame();
  void render(EntityManager &entityManager, SystemManager &systemManager, ComponentManager &componentManager);
  void endFrame();
};
