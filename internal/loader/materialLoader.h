
#pragma once

#include <array>
#include <filesystem>
#include <glad/glad.h>
#include <memory>
#include <model/material.h>
#include <stb_image/stb_image.h>
#include <string>

class MaterialLoader {
public:
  static std::unique_ptr<Material> loadMaterial(const std::string &textureDirectory, float shininess = 32.0f);

private:
  static GLuint loadTextureFromFile(const std::filesystem::path &filePath,
                                    const std::array<unsigned char, 3> &fallbackColor);
};
