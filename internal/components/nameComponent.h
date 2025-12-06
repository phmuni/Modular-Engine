#pragma once

#include "foundation/ecs/componentManager.h"
#include <string>

struct NameComponent : public BaseComponent {
  std::string name;

  NameComponent(const std::string &n) : name(n) {}
};