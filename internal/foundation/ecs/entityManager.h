#pragma once
#include <unordered_set>

using Entity = int;

// Manages entity lifecycle (creation/destruction) in ECS
class EntityManager {
private:
  Entity m_nextEntityID = 0;
  std::unordered_set<Entity> m_activeEntities;

public:
  Entity createEntity();
  void destroyEntity(Entity entity);

  bool isAlive(Entity entity) const { return m_activeEntities.count(entity) > 0; }
};
