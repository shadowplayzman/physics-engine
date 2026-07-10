# 3D Physics Engine

A real-time 3D gravity simulation and physics engine written in **C++** using **OpenGL**.

The project began as a simple renderer and has evolved into an interactive sandbox capable of simulating planetary systems, spawning custom celestial bodies, and visualizing Newtonian gravity in real time.

---

# Screenshot

> Add your best screenshot here.

```md
![Solar System](Images/Overview.png)
```

---

# Features

## Physics

- Newtonian N-body gravity simulation
- Real-time orbital mechanics
- Adjustable simulation speed
- Pause / Resume simulation
- Complete simulation reset
- Runtime planet spawning
- Editable planet mass and radius
- Editable planet velocity

## Rendering

- OpenGL 3.3 Core
- Procedurally generated sphere meshes
- Phong lighting
- Material system
- Texture mapping
- Emissive Sun
- Skybox
- Orbit trail rendering
- Saturn ring rendering
- Camera orbit system
- Smooth camera transitions

## Sandbox Tools

- Planet inspector
- Planet spawner
- Planet templates
- Planet color picker
- Trail color picker
- Camera target switching
- Time controls

---

# Engine Architecture

```
Application
│
├── Universe
│   ├── CelestialBody
│   ├── Gravity Solver
│   └── Physics Update
│
├── Rendering
│   ├── Mesh
│   ├── Material
│   ├── Texture
│   ├── Shader
│   ├── Skybox
│   └── Trail Renderer
│
├── Camera
│
├── UI
│   ├── Planet Inspector
│   ├── Simulation Controls
│   └── Planet Spawner
│
└── SolarSystemFactory
```

---

# Controls

| Key | Action |
|------|--------|
| Left Mouse | Rotate Camera |
| Mouse Wheel | Zoom |
| TAB | Cycle Camera Target |

The simulation can also be controlled through the ImGui interface.

---

# Technologies

- C++
- OpenGL
- GLFW
- GLEW
- GLM
- stb_image
- Assimp
- ImGui

---

# Current Features

- Solar System simulation
- Interactive camera
- Runtime body creation
- Skybox
- Textured planets
- Emissive Sun
- Saturn rings
- Orbit trails
- Material system
- Reset simulation

---

# Future Goals

## Version 2

- Velocity Verlet Integrator
- RK4 Integrator
- Barnes-Hut Gravity
- Collision Detection
- Collision Resolution
- Octree
- Rigid Body Dynamics
- Angular Momentum
- Constraints
- Physics Debug Renderer

---

# Gallery

```
Images/

Overview.png
Earth.png
Saturn.png
Planet_spawner.png
Planet_Inspector.png
Simulation.png
```

---

# License

This project is for educational purposes and personal engine development.
