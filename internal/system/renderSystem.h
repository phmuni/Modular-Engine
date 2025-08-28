#pragma once

#include "core/renderer.h"
#include "ecs/componentManager.h"
#include "ecs/entityManager.h"
#include "ecs/systemManager.h"

#include <vector>

class RenderSystem {
public:
  struct RenderQueue {
    RenderQueue(Entity entity) : entity(entity) {}
    Entity entity;
  };

  void addRenderable(Entity entity);
  void removeRenderable(Entity entity);

  void renderCall(SystemManager &systemManager, EntityManager &entityManager, ComponentManager &componentManager);

  Renderer &getRenderer();
  const std::vector<RenderQueue> &getRenderQueue() const;

private:
  std::vector<RenderQueue> m_entries;
  Renderer m_renderer;

  void setupLights();
};
