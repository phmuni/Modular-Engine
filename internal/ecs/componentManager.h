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
  // Stores component maps by type
  std::unordered_map<std::type_index, std::unordered_map<Entity, std::unique_ptr<BaseComponent>>> storage;

public:
  // Adds a component of type T to the entity
  template <typename T> void add(Entity entity, std::unique_ptr<T> component) {
    storage[std::type_index(typeid(T))][entity] = std::move(component);
  }

  // Accesses a component of type T from the entity
  template <typename T> T &get(Entity entity) {
    auto &map = storage.at(std::type_index(typeid(T)));
    auto it = map.find(entity);
    if (it == map.end())
      throw std::runtime_error("Component not found.");
    return *static_cast<T *>(it->second.get());
  }

  // Checks if the entity has a component of type T
  template <typename T> bool has(Entity entity) {
    auto it = storage.find(std::type_index(typeid(T)));
    if (it == storage.end())
      return false;
    return it->second.find(entity) != it->second.end();
  }

  template <typename T> Entity entityWithComponent() {
    auto it = storage.find(std::type_index(typeid(T)));
    if (it == storage.end())
      return -1;

    for (const auto &[entity, _] : it->second) {
      return entity;
    }

    return -1;
  }

  // Removes all components from the entity (of all types)
  void removeAll(Entity entity) {
    for (auto &[_, map] : storage) {
      map.erase(entity);
    }
  }

  // Removes a specific component from the entity
  template <typename T> void remove(Entity entity) {
    auto &map = storage[std::type_index(typeid(T))];
    map.erase(entity);
  }
};
