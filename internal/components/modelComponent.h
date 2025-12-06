#pragma once

#include "foundation/ecs/componentManager.h"
#include "rendering/resources/material.h"
#include "rendering/resources/mesh.h"

struct ModelComponent : public BaseComponent {
  std::unique_ptr<Mesh> mesh;
  std::unique_ptr<Material> material;

  ModelComponent(std::unique_ptr<Mesh> mesh, std::unique_ptr<Material> mats)
      : mesh(std::move(mesh)), material(std::move(mats)) {}
};
