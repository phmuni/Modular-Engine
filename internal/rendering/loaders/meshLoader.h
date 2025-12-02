#pragma once

#include "rendering/resources/mesh.h"
#include <memory>
#include <string>
#include <tiny_obj_loader/tiny_obj_loader.h>

class MeshLoader {
public:
  static std::unique_ptr<Mesh> loadFromOBJ(const std::string &filename);
};
