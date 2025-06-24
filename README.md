# Modular C++ / OpenGL Engine

A modular graphics engine developed in C++ using SDL3 and modern OpenGL. It follows an ECS (Entity-Component-System) architecture for flexible and scalable system/component management.

## Features

- ECS-based architecture (systems and components decoupled)
- Shadow mapping (depth-based lighting)
- Diffuse lighting with multiple light types (directional, spot)
- OBJ model loading with texture support
- Camera system with yaw, pitch and FOV control
- Real-time rendering using modern OpenGL and shaders

## Build

### Requirements

- CMake
- SDL3
- GLAD
- GLM
- stb_image
- tinyobjloader

### How to compile

```bash
git clone https://github.com/phmuni/Modular-Engine.git
cd Modular-Engine
cmake -S . -B build
cmake --build build
