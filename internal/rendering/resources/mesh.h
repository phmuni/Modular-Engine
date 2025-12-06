#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream> // IWYU pragma: keep
#include <string>
#include <vector>

struct Vertex {
  glm::vec3 position; // vertex position
  glm::vec3 normal;   // vertex normal
  glm::vec2 texCoord; // texture coordinate
};
// struct Submesh {
//   uint32_t indexStart;
//   uint32_t indexCount;
// };

class Mesh {
private:
  GLuint m_VAO, m_VBO, m_EBO;
  std::vector<Vertex> m_vertices;
  std::vector<uint32_t> m_indices;
  // std::vector<Submesh> m_submeshes;

  // initialize VAO/VBO/EBO
  void setupBuffers();

  // load mesh data from OBJ file
  bool loadOBJ(const std::string &filename);

public:
  Mesh() {}

  // load mesh directly from OBJ file
  Mesh(const std::string &filename);

  // create mesh from given vertices and indices
  Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

  ~Mesh();

  // return VAO handle
  GLuint getVAO() const;

  // return number of indices
  size_t getIndexCount() const;
  // std::vector<Submesh> &getSubmeshes();
  // replace vertices and indices
  void setVerticesIndices(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
};
