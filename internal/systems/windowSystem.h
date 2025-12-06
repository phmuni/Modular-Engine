#pragma once

#include "SDL3/SDL_video.h"
#include "foundation/ecs/systemManager.h"
#include "rendering/renderer.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>

// Manages the main window and OpenGL context.
// Handles initialization, resize events, and cursor settings.
class WindowSystem : public BaseSystem {
private:
  SDL_Window *m_window;
  SDL_GLContext m_glContext;

public:
  // create window system with target screen size
  WindowSystem(float screenWidth, float screenHeight);

  // initialize window and GL context
  bool initialize(float screenWidth, float screenHeight);

  // handle window resize events
  void onResize(int newWidth, int newHeight, Renderer &renderer);

  // getters
  SDL_Window *getWindow() const;
  SDL_GLContext getContext() const;

  // enable/disable mouse cursor visibility
  void setCursor(bool boolean);
};
