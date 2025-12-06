#pragma once

#include "components/cameraComponent.h"
#include "foundation/ecs/componentManager.h"
#include "foundation/ecs/systemManager.h"
#include "systems/inputSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Handles camera movement and matrix generation.
// Uses input system to update camera rotation and position.
// Stores the active camera entity.
class CameraSystem : public BaseSystem {
private:
  ComponentManager &m_componentManager;
  InputSystem &m_input;
  Entity m_activeCamera;

public:
  CameraSystem(ComponentManager &cm, InputSystem &in) : m_componentManager(cm), m_input(in), m_activeCamera(-1) {}

  // update camera each frame
  void update(float deltaTime, SystemManager &systemManager);

  // recalculate camera front vector
  void updateFront(CameraComponent &cam);

  // apply mouse-based rotation
  void rotateCamera(CameraComponent &cam);

  // apply keyboard movement
  void moveCamera(CameraComponent &cam, float deltaTime);

  // get view matrix
  glm::mat4 getViewMatrix(const CameraComponent &cam) const;

  // get projection matrix
  glm::mat4 getProjMatrix(const CameraComponent &cam) const;

  // return active camera entity
  Entity getActiveCamera() const;

  // clear active camera
  void removeActiveCamera();

  // set new active camera
  void setActiveCamera(Entity newCamera);
};
