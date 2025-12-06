#include "foundation/core/engine.h"
#include "foundation/core/config.h"

#include "systems/cameraSystem.h"
#include "systems/inputSystem.h"
#include "systems/lightSystem.h"
#include "systems/renderSystem.h"
#include "systems/sceneSystem.h"
#include "systems/shaderSystem.h"
#include "systems/timeSystem.h"
#include "systems/transformSystem.h"
#include "systems/uiSystem.h"
#include "systems/windowSystem.h"

Engine::~Engine() { SDL_Quit(); }

bool Engine::init() {

  registerSystems();

  if (!loadResources()) {
    SDL_Log("Failed to load resources.");
    return false;
  }

  return true;
}

void Engine::registerSystems() {
  systemManager.insert<WindowSystem>(m_screenWidth, m_screenHeight);
  systemManager.insert<InputSystem>();
  systemManager.insert<TimeSystem>();
  systemManager.insert<ShaderSystem>();
  systemManager.insert<RenderSystem>();
  systemManager.insert<TransformSystem>();
  systemManager.insert<CameraSystem>(componentManager, systemManager.getSystem<InputSystem>());
  systemManager.insert<LightSystem>();
  systemManager.insert<SceneSystem>(entityManager, componentManager, systemManager);
  systemManager.insert<UISystem>(systemManager.getSystem<WindowSystem>().getWindow(),
                                 systemManager.getSystem<WindowSystem>().getContext());
}

bool Engine::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath) {
  auto &shaderSystem = systemManager.getSystem<ShaderSystem>();
  if (!shaderSystem.loadShader(name.c_str(), vertexPath.c_str(), fragmentPath.c_str())) {
    SDL_Log("Failed to load shader '%s'!", name.c_str());
    return false;
  }
  return true;
}

bool Engine::loadResources() {
  auto &renderer = systemManager.getSystem<RenderSystem>().getRenderer();
  auto &windowSystem = systemManager.getSystem<WindowSystem>();
  renderer.init(windowSystem.getWindow());

  return loadShader("base", EngineConfig::SHADER_VERTEX, EngineConfig::SHADER_FRAGMENT) &&
         loadShader("shadow", EngineConfig::SHADER_VERTEX_SHADOW, EngineConfig::SHADER_FRAGMENT_SHADOW);
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

void Engine::update(bool &running) {
  auto &inputSystem = systemManager.getSystem<InputSystem>();
  auto &timeSystem = systemManager.getSystem<TimeSystem>();
  auto &cameraSystem = systemManager.getSystem<CameraSystem>();
  auto &windowSystem = systemManager.getSystem<WindowSystem>();

  inputSystem.update(&running, systemManager);
  timeSystem.update();
  cameraSystem.update(timeSystem.getDeltaTime(), systemManager);
}

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

void Engine::createCameraEntity(glm::vec3 position, float yaw, float pitch, float fov) {
  auto &sceneSystem = systemManager.getSystem<SceneSystem>();
  sceneSystem.createCameraEntity(position, yaw, pitch, fov);
}

void Engine::createModelEntity(const std::string &name, const std::string &modelPath, const std::string &texturePath,
                               glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
  auto &sceneSystem = systemManager.getSystem<SceneSystem>();
  sceneSystem.createModelEntity(name, modelPath, texturePath, position, rotation, scale);
}

void Engine::createLightEntity(const std::string &name, glm::vec3 position, glm::vec3 direction, glm::vec3 color,
                               LightType type, float intensity, float cutOff, float outerCutOff) {
  auto &sceneSystem = systemManager.getSystem<SceneSystem>();
  sceneSystem.createLightEntity(name, position, direction, color, type, intensity, cutOff, outerCutOff);
}
