#pragma once
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

using Entity = int;

class BaseComponent {
public:
  virtual ~BaseComponent() = default;
};

class ComponentManager {
private:
  // Stores: component type → (entity → component)
  std::unordered_map<std::type_index, std::unordered_map<Entity, std::unique_ptr<BaseComponent>>> m_storage;

public:
  // Insert a component for an entity
  template <typename T> void insert(Entity entity, std::unique_ptr<T> component) {
    m_storage[std::type_index(typeid(T))][entity] = std::move(component);
  }

  // Get a component (throws if missing)
  template <typename T> T &get(Entity entity) {
    auto &map = m_storage.at(std::type_index(typeid(T)));
    auto it = map.find(entity);
    if (it == map.end()) {
      throw std::runtime_error("Component not found for entity");
    }
    return *static_cast<T *>(it->second.get());
  }

  // Try to get a component (returns nullptr if missing)
  template <typename T> T *tryGet(Entity entity) {
    auto it = m_storage.find(std::type_index(typeid(T)));
    if (it == m_storage.end())
      return nullptr;

    auto cit = it->second.find(entity);
    if (cit == it->second.end())
      return nullptr;

    return static_cast<T *>(cit->second.get());
  }

  // Check if an entity has a component
  template <typename T> bool has(Entity entity) {
    auto it = m_storage.find(std::type_index(typeid(T)));
    if (it == m_storage.end())
      return false;
    return it->second.find(entity) != it->second.end();
  }

  // Get any entity that has this component type (returns -1 if none)
  template <typename T> Entity findEntityWith() {
    auto it = m_storage.find(std::type_index(typeid(T)));
    if (it == m_storage.end())
      return -1;
    if (it->second.empty())
      return -1;
    return it->second.begin()->first;
  }

  // Remove all components for an entity
  void removeAll(Entity entity) {
    for (auto &[_, map] : m_storage)
      map.erase(entity);
  }

  // Remove a specific component type from an entity
  template <typename T> void remove(Entity entity) { m_storage[std::type_index(typeid(T))].erase(entity); }
};
