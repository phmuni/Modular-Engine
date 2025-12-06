#pragma once
#include "glm/ext/vector_float3.hpp"
#include <cstdint>
#include <filesystem>
#include <glad/glad.h>
#include <string>

class Material {
private:
  GLuint m_diffuse = 0;
  GLuint m_specular = 0;
  GLuint m_normal = 0;
  GLuint m_emission = 0;
  float m_shininess = 32.0f;

  uint32_t m_shader;

  static GLuint loadTexture(const std::filesystem::path &path, const std::array<unsigned char, 3> &fallbackColor);

public:
  Material() {};

  // Construtor que carrega texturas do diretório
  Material(const std::string &textureDirectory, float shininess = 32.0f);

  // Construtor direto com texturas já carregadas
  Material(GLuint diffuse, GLuint specular, GLuint normal, GLuint emission, float shininess = 32.0f);

  GLuint getDiffuse() const;
  GLuint getSpecular() const;
  GLuint getNormal() const;
  GLuint getEmission() const;
  float getShininess() const;
  uint32_t getShader() const;

  void setDiffuse(std::string path);
  void setSpecular(std::string path);
  void setNormal(std::string path);
  void setEmission(std::string path);
  void setShininess(float shine);
  void setFallbackColor(glm::vec3 fallback);
  void setShader(uint32_t handle) const;
};