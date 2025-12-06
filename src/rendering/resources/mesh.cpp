#define TINYOBJLOADER_IMPLEMENTATION
#include "rendering/resources/mesh.h"
#include <tiny_obj_loader/tiny_obj_loader.h>

// Construtor que carrega de arquivo OBJ
Mesh::Mesh(const std::string &filename) : m_VAO(0), m_VBO(0), m_EBO(0) {
  if (!loadOBJ(filename)) {
    std::cerr << "[Mesh] Failed to load OBJ file: " << filename << std::endl;
  }
}

// Construtor com vértices e índices
Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices), m_VAO(0), m_VBO(0), m_EBO(0) {
  setupBuffers();
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
  glDeleteBuffers(1, &m_EBO);
}

void Mesh::setupBuffers() {
  if (m_vertices.empty() || m_indices.empty()) {
    std::cerr << "Erro: Vertices ou índices não definidos!" << std::endl;
    return;
  }

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

GLuint Mesh::getVAO() const { return m_VAO; }

size_t Mesh::getIndexCount() const { return m_indices.size(); }
// std::vector<Submesh> &Mesh::getSubmeshes() { return m_submeshes; }

void Mesh::setVerticesIndices(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
  this->m_vertices = vertices;
  this->m_indices = indices;
  setupBuffers();
}

bool Mesh::loadOBJ(const std::string &filename) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;
  std::string baseDir = filename.substr(0, filename.find_last_of("/\\") + 1);

  bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str(), baseDir.c_str());

  if (!err.empty())
    std::cerr << "[Mesh] Error: " << err << std::endl;

  if (!success)
    return false;

  // For each face of each shape, we always create a new Vertex
  for (const auto &shape : shapes) {
    for (const auto &idx : shape.mesh.indices) {
      Vertex vertex{};

      vertex.position = {attrib.vertices[3 * idx.vertex_index + 0], attrib.vertices[3 * idx.vertex_index + 1],
                         attrib.vertices[3 * idx.vertex_index + 2]};

      // Normal, If it exists
      if (idx.normal_index >= 0) {
        vertex.normal = {attrib.normals[3 * idx.normal_index + 0], attrib.normals[3 * idx.normal_index + 1],
                         attrib.normals[3 * idx.normal_index + 2]};
      }

      if (idx.texcoord_index >= 0) {
        vertex.texCoord = {attrib.texcoords[2 * idx.texcoord_index + 0],
                           1.0f - attrib.texcoords[2 * idx.texcoord_index + 1]};
      }

      m_vertices.emplace_back(vertex);
      m_indices.emplace_back(static_cast<unsigned int>(m_vertices.size() - 1));
    }
  }

  setupBuffers();
  return true;
}