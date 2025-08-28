#pragma once

#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <core/renderer.h>
#include <glad/glad.h>

class WindowSystem {
private:
  SDL_Window *window;
  SDL_GLContext glContext;

public:
  WindowSystem(float screenWidth, float screenHeight);

  bool initialize(float screenWidth, float screenHeight);

  void onResize(int newWidth, int newHeight, Renderer &renderer);

  SDL_Window *getWindow() const;
  SDL_GLContext getContext() const;
  void setCursor(bool boolean);
};