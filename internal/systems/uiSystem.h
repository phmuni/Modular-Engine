#pragma once

#include "SDL3/SDL_video.h"
#include "foundation/ecs/entityManager.h"
#include "foundation/ecs/systemManager.h"

// Handles UI rendering and entity selection.
// Wraps ImGui frame lifecycle: begin, render, end.
class UISystem : public BaseSystem {
public:
  Entity m_selectedEntity = -1;

  // initialize UI with window and GL context
  UISystem(SDL_Window *w, SDL_GLContext gl);

  // start ImGui frame
  void beginFrame();

  // draw UI panels and widgets
  void render(EntityManager &entityManager, SystemManager &systemManager, ComponentManager &componentManager);

  // finalize ImGui frame
  void endFrame();
};
