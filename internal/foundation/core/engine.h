#pragma once

// External Includes
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Internal Includes
#include "components/lightComponent.h"
#include "foundation/core/config.h"

// ECS & Systems
#include "foundation/ecs/componentManager.h"
#include "foundation/ecs/entityManager.h"
#include "foundation/ecs/systemManager.h"

// Central engine coordinator using Entity-Component-System (ECS) architecture.
// ECS provides data-driven design that separates data (components) from behavior (systems),
// enabling better composition, cache locality, and system independence.
class Engine {
private:
  float m_screenWidth;
  float m_screenHeight;

  EntityManager entityManager;
  ComponentManager componentManager;
  SystemManager systemManager;

  void update(bool &running);
  void render();
  void loop(bool &running);
  bool loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
  bool loadResources();

public:
  Engine() : m_screenWidth(EngineConfig::DEFAULT_SCREEN_WIDTH), m_screenHeight(EngineConfig::DEFAULT_SCREEN_HEIGHT) {}
  ~Engine();

  bool init();
  void registerSystems();
  void run();

  void createCameraEntity(glm::vec3 position, float yaw = 0.0f, float pitch = 0.0f, float fov = 90.0f);

  void createModelEntity(const std::string &name, const std::string &modelPath, const std::string &texturePath,
                         glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

  void createLightEntity(const std::string &name, glm::vec3 position, glm::vec3 direction, glm::vec3 color,
                         LightType type, float intensity, float cutOff, float outerCutOff);
};
