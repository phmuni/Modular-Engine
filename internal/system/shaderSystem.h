#pragma once
#include "loader/shaderLoader.h"
#include <memory>
#include <string>
#include <unordered_map>

class ShaderSystem {
private:
  std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

public:
  ShaderSystem() = default;

  bool loadShader(const std::string &name, const char *vertexPath, const char *fragmentPath);
  Shader &getShader(const std::string &name);
  void unloadShader(const std::string &name);
  void clear();
};
