#pragma once

#include "foundation/ecs/componentManager.h"
#include "foundation/ecs/entityManager.h"
#include "foundation/ecs/systemManager.h"
#include "rendering/renderer.h"

#include <vector>

// Handles the rendering process.
// Stores renderable entities and performs shadow pass + main pass.
class RenderSystem : public BaseSystem {
public:
  // add entity to render list
  void insertRenderable(Entity entity);

  // remove entity from render list
  void removeRenderable(Entity entity);

  // main render call
  void renderCall(SystemManager &systemManager, EntityManager &entityManager, ComponentManager &componentManager);

  // access the renderer
  Renderer &getRenderer();

  // return render queue list
  const std::vector<Entity> &getRenderQueue() const;

private:
  std::vector<Entity> m_entries;
  Renderer m_renderer;

  // prepare shader light uniforms
  void setupLights();
};
