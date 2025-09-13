#include "core/engine.h"

// Forward declarations
void createDefaultModel(const std::string &name, Engine &engine);
void createDefaultModel2(const std::string &name, Engine &engine);
void createSpotlight(const std::string &name, Engine &engine);
void createDirectionalLight(const std::string &name, Engine &engine);
void createCamera(Engine &engine);

int main() {
  Engine engine;

  if (!engine.initialize()) {
    SDL_Log("Failed to initialize engine!");
    return 1;
  }

  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

  createDefaultModel("Backpack", engine);
  createDefaultModel2("Backpack2", engine);
  createDirectionalLight("Directional 1", engine);
  createCamera(engine);

  engine.run();
  return 0;
}

void createDefaultModel(const std::string &name, Engine &engine) {
  const std::string modelPath = "../assets/models/backpack/backpack.obj";
  const std::string texturePath = "../assets/models/backpack/";

  glm::vec3 position(0.0f);
  glm::vec3 rotation(0.0f);
  glm::vec3 scale(1.0f);

  engine.createEntityModel(name, modelPath, texturePath, position, rotation, scale);
}
void createDefaultModel2(const std::string &name, Engine &engine) {
  const std::string modelPath = "../assets/models/backpack/backpack.obj";
  const std::string texturePath = "../assets/models/backpack/";

  glm::vec3 position(1.0f);
  glm::vec3 rotation(0.0f);
  glm::vec3 scale(1.0f);

  engine.createEntityModel(name, modelPath, texturePath, position, rotation, scale);
}

void createSpotlight(const std::string &name, Engine &engine) {
  glm::vec3 position(3.0f, 3.0f, 0.0f);
  glm::vec3 direction(-1.0f, -1.0f, 0.0f);
  glm::vec3 color(1.0f);

  float intensity = 1.5f;
  float cutOff = glm::cos(glm::radians(15.0f));
  float outerCutOff = glm::cos(glm::radians(25.0f));

  engine.createEntityLight(name, position, direction, color, LightType::Spot, intensity, cutOff, outerCutOff);
}
void createDirectionalLight(const std::string &name, Engine &engine) {
  glm::vec3 position(3.0f, 3.0f, 0.0f);
  glm::vec3 direction(-1.0f, -1.0f, 0.0f);
  glm::vec3 color(1.0f);
  float intensity = 1.5f;

  float cutOff = 0.0f;
  float outerCutOff = 0.0f;

  engine.createEntityLight(name, position, direction, color, LightType::Directional, intensity, cutOff, outerCutOff);
}

void createCamera(Engine &engine) {

  glm::vec3 position(0.0f, 3.0f, 8.0f);
  float yaw = 0.0f;
  float pitch = -15.0f;
  float fov = 90.0f;

  engine.createEntityCamera(position, yaw, pitch, fov);
}
