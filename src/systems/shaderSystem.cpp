#include "systems/shaderSystem.h"

bool ShaderSystem::loadShader(const std::string &name, const char *vertexPath, const char *fragmentPath) {
  if (m_shaders.count(name)) {
    return false;
  }
  m_shaders[name] = std::make_shared<Shader>(vertexPath, fragmentPath);
  return true;
}

Shader &ShaderSystem::getShader(const std::string &name) { return *m_shaders.at(name); }

void ShaderSystem::unloadShader(const std::string &name) { m_shaders.erase(name); }

void ShaderSystem::clear() { m_shaders.clear(); }
