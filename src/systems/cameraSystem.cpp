#include "systems/cameraSystem.h"
#include "components/cameraComponent.h"
#include "systems/inputSystem.h"
#include "systems/windowSystem.h"

void CameraSystem::update(float deltaTime, SystemManager &systemManager) {
  Entity entity = getActiveCamera();
  if (!m_componentManager.has<CameraComponent>(entity))
    return;

  auto &cam = m_componentManager.get<CameraComponent>(entity);
  auto &inputSystem = systemManager.getSystem<InputSystem>();
  auto &windowSystem = systemManager.getSystem<WindowSystem>();
  if (inputSystem.getMove()) {
    rotateCamera(cam);
    moveCamera(cam, deltaTime);
    windowSystem.setCursor(true);
  } else {
    windowSystem.setCursor(false);
  }

  updateFront(cam);
}

glm::mat4 CameraSystem::getViewMatrix(const CameraComponent &cam) const {
  return glm::lookAt(cam.position, cam.position + cam.front, cam.up);
}

glm::mat4 CameraSystem::getProjMatrix(const CameraComponent &cam) const {
  return glm::perspective(glm::radians(cam.fov), cam.aspectRatio, 0.1f, 100.0f);
}

void CameraSystem::updateFront(CameraComponent &cam) {
  cam.front =
      glm::normalize(glm::vec3(cos(glm::radians(cam.pitch)) * sin(glm::radians(cam.yaw)), sin(glm::radians(cam.pitch)),
                               -cos(glm::radians(cam.pitch)) * cos(glm::radians(cam.yaw))));
}

void CameraSystem::rotateCamera(CameraComponent &cam) {
  float xoffset = m_input.getMouseXOffset() * cam.mouseSensitivity / cam.smoothFactor;
  float yoffset = m_input.getMouseYOffset() * cam.mouseSensitivity / cam.smoothFactor;

  cam.yaw += xoffset;
  cam.pitch -= yoffset;

  if (cam.yaw >= 360.0f)
    cam.yaw -= 360.0f;
  else if (cam.yaw < 0.0f)
    cam.yaw += 360.0f;

  cam.pitch = glm::clamp(cam.pitch, -89.9f, 89.9f);
}

void CameraSystem::moveCamera(CameraComponent &cam, float deltaTime) {
  float velocity = cam.moveSpeed * deltaTime;
  float angleRad = glm::radians(-cam.yaw);
  float cosAngle = cos(angleRad);
  float sinAngle = sin(angleRad);

  if (m_input.isActionPressed(Action::MoveForward)) {
    cam.position.z -= cosAngle * velocity;
    cam.position.x -= sinAngle * velocity;
  }
  if (m_input.isActionPressed(Action::MoveBackward)) {
    cam.position.z += cosAngle * velocity;
    cam.position.x += sinAngle * velocity;
  }
  if (m_input.isActionPressed(Action::MoveLeft)) {
    cam.position.z += sinAngle * velocity;
    cam.position.x -= cosAngle * velocity;
  }
  if (m_input.isActionPressed(Action::MoveRight)) {
    cam.position.z -= sinAngle * velocity;
    cam.position.x += cosAngle * velocity;
  }
  if (m_input.isActionPressed(Action::MoveUp)) {
    cam.position.y += velocity;
  }
  if (m_input.isActionPressed(Action::MoveDown)) {
    cam.position.y -= velocity;
  }
}

Entity CameraSystem::getActiveCamera() const { return m_activeCamera; }

void CameraSystem::removeActiveCamera() { m_activeCamera = -1; }

void CameraSystem::setActiveCamera(Entity newCamera) { m_activeCamera = newCamera; }
