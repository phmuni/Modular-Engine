#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
private:
  GLuint shaderID;

  // read shader source file
  std::string readShaderFile(const char *filename) const;

  // compile a single shader (vertex/fragment)
  GLuint compileShader(GLenum type, const char *filename);

  // link vertex + fragment into a shader program
  GLuint createShaderProgram(const char *vertexShaderFile, const char *fragmentShaderFile);

public:
  Shader() : shaderID(0) {}

  // build shader directly from files
  Shader(const char *vertexShaderFile, const char *fragmentShaderFile);

  // load and compile shaders
  bool load(const char *vertexShaderFile, const char *fragmentShaderFile);

  // activate shader program
  void use() const;

  // set uniform textures
  void setTex(const char *name, GLuint textureID, int textureUnit) const;

  // set uniform values
  void setInt(const char *name, int value) const;
  void setFloat(const char *name, float value) const;
  void setVec3(const char *name, glm::vec3 value) const;
  void setMat3(const char *name, glm::mat3 value) const;
  void setMat4(const char *name, glm::mat4 value) const;

  // return shader program ID
  GLuint getShaderID() const;
};
