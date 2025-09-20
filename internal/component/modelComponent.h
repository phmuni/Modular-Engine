#pragma once

#include "ecs/componentManager.h"
#include "model/material.h"
#include "model/mesh.h"
#include <memory>
#include <utility>

struct ModelComponent : public BaseComponent {
  std::unique_ptr<Mesh> mesh;
  std::unique_ptr<Material> material;

  ModelComponent(std::unique_ptr<Mesh> mesh, std::unique_ptr<Material> material)
      : mesh(std::move(mesh)), material(std::move(material)) {}
};
