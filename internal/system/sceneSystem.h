#pragma once

#include "component/lightComponent.h"
#include "ecs/componentManager.h"
#include "ecs/entityManager.h"
#include "ecs/systemManager.h"
#include "glm/ext/vector_float3.hpp"
#include <string>

class SceneSystem {
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