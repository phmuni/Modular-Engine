#pragma once
#include <SDL3/SDL.h>
#include <glad/glad.h>

class Mesh;
struct Submesh;

class Renderer {
private:
  SDL_Window *m_window = nullptr;

  // Shadow mapping
  GLuint m_depthMapFBO = 0;
  GLuint m_depthMap = 0;
  const int m_shadowWidth = 4096;
  const int m_shadowHeight = 4096;

  // Viewport
  int m_screenWidth = 1280;
  int m_screenHeight = 720;

  void initShadowMapping();

public:
  void init(SDL_Window *window);

  // Main render pass
  void beginFrame() const;
  void endFrame() const;

  // Drawing
  void drawMesh(const Mesh &mesh) const;
  void drawSubmesh(const Mesh &mesh, const Submesh &submesh) const;

  // Shadow pass
  void beginShadowPass();
  void endShadowPass();

  // Getters
  GLuint getDepthMap() const;
  GLuint getDepthMapFBO() const;

  void setViewportSize(int width, int height);
};
