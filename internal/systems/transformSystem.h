#pragma once

#include "components/transformComponent.h"
#include "foundation/ecs/systemManager.h"
#include <glm/glm.hpp>

// Builds model matrices from position, rotation, and scale.
class TransformSystem : public BaseSystem {
public:
  TransformSystem() = default;

  // compute model matrix for a transform component
  glm::mat4 calculateModelMatrix(const TransformComponent &transform);
};
