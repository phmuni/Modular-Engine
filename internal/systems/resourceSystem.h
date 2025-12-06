#pragma once

#include "foundation/ecs/systemManager.h"
#include "rendering/resources/material.h"
#include "rendering/resources/mesh.h"
#include "rendering/resources/shader.h"
#include <cstdint>
#include <memory>
#include <unordered_map>

class ResourceSystem : public BaseSystem {
private:
  std::unordered_map<uint32_t, std::unique_ptr<Mesh>> m_meshes;
  std::unordered_map<uint32_t, std::unique_ptr<Material>> m_materials;
  std::unordered_map<uint32_t, std::unique_ptr<Shader>> m_shaders;

  uint32_t nextMesh = 1;
  uint32_t nextMaterial = 1;
  uint32_t nextShder = 1;

public:
  uint32_t loadMesh(std::string path);
  Mesh &getMesh(uint32_t handle);
  void unloadMesh(uint32_t handle);

  uint32_t loadMaterial();
  Material &getMaterial(uint32_t handle);
  void unloadMaterial(uint32_t handle);

  uint32_t loadShader(const std::string vpath, const std::string fpath);
  Shader &getShader(uint32_t handle);
  void unloadShader(uint32_t handle);
};