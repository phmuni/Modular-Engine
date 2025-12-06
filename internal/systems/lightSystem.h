#pragma once

#include "foundation/ecs/componentManager.h"
#include "foundation/ecs/systemManager.h"
#include "rendering/resources/shader.h"
#include <vector>

// Stores and manages all light entities.
// Handles adding/removing lights and sending light data to the shader.
class LightSystem : public BaseSystem {
public:
  // add a light entity to the system
  void createLight(Entity entity);

  // remove a light entity from the system
  void destroyLight(Entity entity);

  // return the current list of light entities
  const std::vector<Entity> &getLights() const;

  // upload all light data to the shader
  void uploadLightsToShader(Shader &shader, ComponentManager &componentManager);

private:
  std::vector<Entity> m_lights;
};
