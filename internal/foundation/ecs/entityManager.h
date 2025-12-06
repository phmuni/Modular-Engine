#pragma once
#include "foundation/ecs/componentManager.h"
#include <unordered_set>

using Entity = int;

class EntityManager {
private:
  Entity m_nextEntityID = 0;
  std::unordered_set<Entity> m_activeEntities; // tracks all active entities

public:
  // Create a new entity and return its ID
  Entity createEntity();

  // Destroy an entity (marks as inactive)
  void destroyEntity(Entity entity);

  // Check if an entity is currently active
  bool isAlive(Entity entity) const { return m_activeEntities.count(entity) > 0; }
};
