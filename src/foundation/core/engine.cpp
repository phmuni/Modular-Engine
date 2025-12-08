#include "foundation/core/engine.h"
#include "foundation/core/config.h"

#include "systems/cameraSystem.h"
#include "systems/inputSystem.h"
#include "systems/lightSystem.h"
#include "systems/renderSystem.h"
#include "systems/resourceSystem.h"
#include "systems/sceneSystem.h"
#include "systems/timeSystem.h"
#include "systems/transformSystem.h"
#include "systems/uiSystem.h"
#include "systems/windowSystem.h"

#include <SDL3/SDL.h>

Engine::Engine()
    : m_screenWidth(EngineConfig::DEFAULT_SCREEN_WIDTH), m_screenHeight(EngineConfig::DEFAULT_SCREEN_HEIGHT) {}

Engine::~Engine() { SDL_Quit(); }

bool Engine::init() {
  registerSystems();

  if (!loadResources()) {
    SDL_Log("Failed to load resources");
    return false;
  }

  return true;
}

// Register all systems in dependency order
void Engine::registerSystems() {
  systemManager.insert<WindowSystem>(m_screenWidth, m_screenHeight);
  systemManager.insert<InputSystem>();
  systemManager.insert<TimeSystem>();
  systemManager.insert<ResourceSystem>();
  systemManager.insert<RenderSystem>();
  systemManager.insert<TransformSystem>();
  systemManager.insert<CameraSystem>(componentManager, systemManager.getSystem<InputSystem>());
  systemManager.insert<LightSystem>();
  systemManager.insert<SceneSystem>(entityManager, componentManager, systemManager);
  systemManager.insert<UISystem>(systemManager.getSystem<WindowSystem>().getWindow(),
                                 systemManager.getSystem<WindowSystem>().getContext());
}

// Load shaders and initialize renderer
bool Engine::loadResources() {
  auto &renderer = systemManager.getSystem<RenderSystem>().getRenderer();
  auto &windowSystem = systemManager.getSystem<WindowSystem>();
  auto &resourceSystem = systemManager.getSystem<ResourceSystem>();

  renderer.init(windowSystem.getWindow());

  // Load base and shadow shaders
  uint32_t baseShader = resourceSystem.loadShader(EngineConfig::SHADER_VERTEX, EngineConfig::SHADER_FRAGMENT);
  uint32_t shadowShader =
      resourceSystem.loadShader(EngineConfig::SHADER_VERTEX_SHADOW, EngineConfig::SHADER_FRAGMENT_SHADOW);

  if (baseShader == 0 && shadowShader == 1) {
    return true;
  }

  SDL_Log("Failed to load shaders");
  return false;
}

void Engine::run() {
  bool running = true;
  loop(running);
}

void Engine::loop(bool &running) {
  while (running) {
    update(running);
    render();
  }
}

// Update all game logic systems
void Engine::update(bool &running) {
  auto &inputSystem = systemManager.getSystem<InputSystem>();
  auto &timeSystem = systemManager.getSystem<TimeSystem>();
  auto &cameraSystem = systemManager.getSystem<CameraSystem>();

  inputSystem.update(&running, systemManager);
  timeSystem.update();
  cameraSystem.update(timeSystem.getDeltaTime(), systemManager);
}

// Render frame: scene + UI
void Engine::render() {
  auto &renderSystem = systemManager.getSystem<RenderSystem>();
  auto &renderer = renderSystem.getRenderer();
  auto &uiSystem = systemManager.getSystem<UISystem>();

  renderer.beginFrame();

  uiSystem.beginFrame();

  renderSystem.renderCall(systemManager, entityManager, componentManager);

  uiSystem.render(entityManager, systemManager, componentManager);
  uiSystem.endFrame();

  renderer.endFrame();
}

// High-level entity creation (delegates to SceneSystem)

void Engine::createCameraEntity(glm::vec3 position, float yaw, float pitch, float fov) {
  auto &sceneSystem = systemManager.getSystem<SceneSystem>();
  sceneSystem.createCameraEntity(position, yaw, pitch, fov);
}

void Engine::createModelEntity(const std::string &name, const std::string &modelPath, glm::vec3 position,
                               glm::vec3 rotation, glm::vec3 scale) {
  auto &sceneSystem = systemManager.getSystem<SceneSystem>();
  sceneSystem.createModelEntity(name, modelPath, position, rotation, scale);
}

void Engine::createLightEntity(const std::string &name, glm::vec3 position, glm::vec3 direction, glm::vec3 color,
                               LightType type, float intensity, float cutOff, float outerCutOff) {
  auto &sceneSystem = systemManager.getSystem<SceneSystem>();
  sceneSystem.createLightEntity(name, position, direction, color, type, intensity, cutOff, outerCutOff);
}
