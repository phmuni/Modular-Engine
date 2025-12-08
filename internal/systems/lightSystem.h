#pragma once
#include "foundation/ecs/componentManager.h"
#include "foundation/ecs/systemManager.h"
#include <vector>

// Forward declarations
class Shader;
class ComponentManager;

// Manages all light entities and uploads light data to shaders
class LightSystem : public BaseSystem {
private:
  std::vector<Entity> m_lights;

public:
  void createLight(Entity entity);
  void destroyLight(Entity entity);

  const std::vector<Entity> &getLights() const;

  // Upload all lights to shader uniform array
  void uploadLightsToShader(Shader &shader, ComponentManager &componentManager);
};
