#pragma once

#include "ecs/componentManager.h"
#include "ecs/systemManager.h"
#include "loader/shaderLoader.h"
#include <vector>

class LightSystem : public BaseSystem {
public:
  void addLight(Entity entity);
  void removeLight(Entity entity);

  const std::vector<Entity> &getLights() const;

  void uploadLightsToShader(Shader &shader, ComponentManager &componentManager);

private:
  std::vector<Entity> m_lights;
};
