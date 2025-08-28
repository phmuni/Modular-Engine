#include "system/windowSystem.h"

WindowSystem::WindowSystem(float screenWidth, float screenHeight) : window(nullptr), glContext(nullptr) {
  initialize(screenWidth, screenHeight);
};

bool WindowSystem::initialize(float screenWidth, float screenHeight) {

  // OpenGL Initialization
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow("Engine", screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!window) {
    SDL_Log("Failed to create the window: %s", SDL_GetError());
    return false;
  }

  glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    SDL_Log("Failed to create the OpenGL context: %s", SDL_GetError());
    return false;
  }

  // GLAD Initialization
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_Log("Failed to initialize GLAD.");
    return false;
  }

  // Flags
  glEnable(GL_DEPTH_TEST);                      // Enables depth testing
  SDL_GL_SetSwapInterval(1);                    // Enable or Disable V-Sync
  SDL_SetWindowRelativeMouseMode(window, true); // Hides and confines the cursor

  return true;
}

void WindowSystem::onResize(int newWidth, int newHeight, Renderer &renderer) {
  renderer.setViewportSize(newWidth, newHeight);
}

SDL_Window *WindowSystem::getWindow() const { return window; }
SDL_GLContext WindowSystem::getContext() const { return glContext; }

void WindowSystem::setCursor(bool boolean) { SDL_SetWindowRelativeMouseMode(window, boolean); }