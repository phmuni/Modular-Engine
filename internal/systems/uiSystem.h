#pragma once
#include "foundation/ecs/systemManager.h"
#include <SDL3/SDL_video.h>

// Forward declarations
class EntityManager;
class SystemManager;
class ComponentManager;
using Entity = int;

class UISystem : public BaseSystem {
public:
  Entity m_selectedEntity = -1;

  UISystem(SDL_Window *window, SDL_GLContext glContext);

  void beginFrame();
  void render(EntityManager &entityManager, SystemManager &systemManager, ComponentManager &componentManager);
  void endFrame();
};
