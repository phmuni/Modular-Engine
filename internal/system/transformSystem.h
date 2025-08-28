#pragma once

#include "component/transformComponent.h"
#include <glm/glm.hpp>

class TransformSystem {
public:
  TransformSystem() = default;
  glm::mat4 calculateModelMatrix(const TransformComponent &transform);
};