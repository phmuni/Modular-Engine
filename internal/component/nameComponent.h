#pragma once

#include "ecs/componentManager.h"
#include <string>

struct NameComponent : public BaseComponent {
  std::string name;

  NameComponent() = default;
  NameComponent(const std::string &n) : name(n) {}
};