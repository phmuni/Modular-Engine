#pragma once
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

class BaseSystem {
public:
  virtual ~BaseSystem() = default;
};

// Manages all systems in ECS (registration and retrieval)
class SystemManager {
private:
  std::unordered_map<std::type_index, std::unique_ptr<BaseSystem>> m_systems;

public:
  // Register system of type T with constructor args
  template <typename T, typename... Args> void insert(Args &&...args);

  // Get system of type T (throws if not found)
  template <typename T> T &getSystem() const;
};

// Template implementations

template <typename T, typename... Args> void SystemManager::insert(Args &&...args) {
  std::type_index typeId(typeid(T));
  auto system = std::make_unique<T>(std::forward<Args>(args)...);
  m_systems[typeId] = std::move(system);
}

template <typename T> T &SystemManager::getSystem() const {
  auto it = m_systems.find(std::type_index(typeid(T)));
  if (it != m_systems.end()) {
    return *static_cast<T *>(it->second.get());
  }
  throw std::runtime_error("System not found");
}
