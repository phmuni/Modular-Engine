#pragma once

#include "components/lightComponent.h"
#include "foundation/ecs/componentManager.h"
#include "foundation/ecs/entityManager.h"
#include "foundation/ecs/systemManager.h"
#include "glm/ext/vector_float3.hpp"
#include <string>

class SceneSystem : public BaseSystem {
private:
  EntityManager &entityManager;
  ComponentManager &componentManager;
  SystemManager &systemManager;

public:
  SceneSystem(EntityManager &em, ComponentManager &cm, SystemManager &sm)
      : entityManager(em), componentManager(cm), systemManager(sm) {}

  void removeEntity(Entity entity);
  void createEntityCamera(glm::vec3 position, float yaw, float pitch, float fov);
  void createEntityModel(const std::string name, const std::string &modelPath, const std::string &texturePath,
                         glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
  void createEntityLight(const std::string &name, glm::vec3 position, glm::vec3 direction, glm::vec3 color,
                         LightType type, float intensity, float cutOff, float outerCutOff);
};