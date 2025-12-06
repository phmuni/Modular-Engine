#pragma once

#include "SDL3/SDL_scancode.h"
#include "foundation/ecs/systemManager.h"
#include <SDL3/SDL.h>
#include <rendering/renderer.h>
#include <unordered_map>

enum class Action { MoveForward, MoveBackward, MoveLeft, MoveRight, MoveUp, MoveDown, MoveMouse };

// Handles keyboard and mouse input.
// Stores key states, mouse offsets, and custom key bindings.
// Also tracks quit events and toggles.
class InputSystem : public BaseSystem {
private:
  float m_mouseXOffset = 0.0f;
  float m_mouseYOffset = 0.0f;
  bool m_quitRequested = false;
  bool m_controlEnabled = true;
  bool m_toggleKeyLastState = false;

  // keyboard state array
  bool m_keys[SDL_SCANCODE_COUNT]{false};

  // action -> key mapping
  std::unordered_map<Action, SDL_Scancode> m_keyBinds;

  // assign default key bindings
  void setDefaultKeyBinds();

public:
  InputSystem();

  // process input and update internal states
  bool update(bool *running, SystemManager &systemManager);

  // getters for state checks
  bool isQuitRequested() const;
  bool isActionPressed(Action action) const;
  bool isKeyPressed(SDL_Scancode key) const;

  float getMouseXOffset() const;
  float getMouseYOffset() const;
  bool getMove() const;

  // setters for internal values
  void setQuitRequested(bool quitRequested);
  void setMouseXOffset(float mouseXOffset);
  void setMouseYOffset(float mouseYOffset);
  void setKeyBind(Action action, SDL_Scancode keyCode);
  void setKeyPressed(SDL_Scancode key, bool pressed);
};
