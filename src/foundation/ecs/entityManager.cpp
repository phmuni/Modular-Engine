#include "foundation/ecs/entityManager.h"

Entity EntityManager::createEntity() {
  Entity entity = nextEntityID++;
  activeEntities.insert(entity);
  return entity;
}

void EntityManager::deleteEntity(Entity entity) { activeEntities.erase(entity); }
