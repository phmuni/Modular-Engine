#pragma once

// External Includes
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Internal Includes
#include "rendering/resources/mesh.h"

class Renderer {
private:
  SDL_Window *m_window = nullptr;

  GLuint m_depthMap = 0;
  GLuint m_depthMapFBO = 0;
  const int m_shadowWidth = 2048;
  const int m_shadowHeight = 2048;

  int m_screenWidth = 1280;
  int m_screenHeight = 720;

  // Create depth map and FBO for shadow pass
  void initShadowMapping();

public:
  // Initialize OpenGL state and attach to window
  void init(SDL_Window *window);

  // Draw a mesh using the active shader
  void drawMesh(const Mesh &mesh) const;

  // Start and end main render pass
  void beginFrame() const;
  void endFrame() const;

  // Start and end shadow depth pass
  void beginShadowPass();
  void endShadowPass();

  // Get shadow depth texture / FBO
  GLuint getDepthMap() const;
  GLuint getDepthMapFBO() const;

  // Update OpenGL viewport size
  void setViewportSize(int width, int height);
};
