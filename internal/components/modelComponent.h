#pragma once

#include "foundation/ecs/componentManager.h"
#include "rendering/resources/material.h"
#include "rendering/resources/mesh.h"
#include <memory>
#include <utility>

struct ModelComponent : public BaseComponent {
  std::unique_ptr<Mesh> mesh;
  std::unique_ptr<Material> material;

  ModelComponent(std::unique_ptr<Mesh> mesh, std::unique_ptr<Material> material)
      : mesh(std::move(mesh)), material(std::move(material)) {}
};
