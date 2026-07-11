# 3D Solar System Simulation
## A 3D Solar System simulator built from scratch in C++ using OpenGL.

This project was built to learn how physics engines and rendering engines work internally. Instead of using an existing game engine or physics library, I wanted to implement everything myself and understand how the different systems fit together.

The project currently simulates the Solar System using Newtonian gravity and includes a sandbox where planets can be edited or spawned while the simulation is running.

Some of the things this project currently includes:

- Real-time Newtonian gravity simulation
- Textured planets
- Saturn rings
- Skybox
- Orbit camera
- Planet spawning
- Planet inspector
- Time controls
- Pause and resume simulation
- Planet and trail color customization
- Orbit trail rendering
- Standalone executable

## Demo

You can watch a short demonstration of the project here:

**Video:** *(https://www.youtube.com/watch?v=hP4zgpyufLg)*

---

## Screenshots

### Solar System

![Overview](Images/Overview.png)

### Earth

![Earth](Images/Earth.png)

### Saturn

![Saturn](Images/saturn.png)

### Planet Inspector

![Inspector](Images/Planet_Inspector.png)

### Planet Spawner

![Spawner](Images/Planet_spawner.png)

### Simulation Controls

![Controls](Images/Simulation.png)

---

## Controls

- Left Mouse Button - Rotate camera
- Mouse Wheel - Zoom
- TAB - Switch between planets

Most simulation controls are available through the ImGui interface.

---

## Technologies Used

This project uses:

- C++
- OpenGL
- GLFW
- GLEW
- GLM
- Dear ImGui
- stb_image

---

## Known Issues

- The application is currently designed for **1920×1080** and has not been adapted for different window sizes or resolutions.
- UI scaling and rendering may not appear correctly at other resolutions.
- I know the saturn rings look terrible, but i tried my best to fix them 

---

## Why I Built This

I started this project because I wanted to understand how a physics engine works instead of treating it like a black box. The goal is to gradually build a complete physics engine while learning more about graphics programming, mathematics, and simulation along the way.

---

## Found a Bug?

If you find a bug or have a suggestion, feel free to open an issue. Pull requests are also welcome.

---

## Project Status

This is the first public version of the project and I'll continue improving it over time.
