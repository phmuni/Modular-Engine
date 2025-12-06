#include "rendering/renderer.h"

void Renderer::init(SDL_Window *window) {
  m_window = window;
  initShadowMapping();
}

void Renderer::beginFrame() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::endFrame() const { SDL_GL_SwapWindow(m_window); }

void Renderer::drawMesh(const Mesh &mesh) const {
  glBindVertexArray(mesh.getVAO());
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndexCount()), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Renderer::beginShadowPass() {
  glViewport(0, 0, m_shadowWidth, m_shadowHeight);
  glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::endShadowPass() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, m_screenWidth, m_screenHeight);
}

void Renderer::initShadowMapping() {
  glGenFramebuffers(1, &m_depthMapFBO);

  glGenTextures(1, &m_depthMap);
  glBindTexture(GL_TEXTURE_2D, m_depthMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
               nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Renderer::getDepthMap() const { return m_depthMap; }

GLuint Renderer::getDepthMapFBO() const { return m_depthMapFBO; }

void Renderer::setViewportSize(int width, int height) {
  m_screenWidth = width;
  m_screenHeight = height;
}
