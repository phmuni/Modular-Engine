#pragma once

#include "foundation/ecs/componentManager.h"
#include "glm/ext/vector_float3.hpp"

struct TransformComponent : public BaseComponent {
  glm::vec3 position{0.0f};
  glm::vec3 rotation{0.0f};
  glm::vec3 scale{1.0f};

  TransformComponent(glm::vec3 pos = {0, 0, 0}, glm::vec3 rot = {0, 0, 0}, glm::vec3 scl = {1, 1, 1})
      : position(pos), rotation(rot), scale(scl) {}
};
