# Physics Engine

A physics and astrophysics engine written from scratch in **C++** using **OpenGL**. The project focuses on building a realistic simulation framework using real-world physics, SI units, and modern engine architecture.

The long-term goal is to evolve this project from a Newtonian gravity simulator into a full astrophysics engine capable of simulating orbital mechanics, N-body systems, and eventually General Relativity phenomena such as black holes, gravitational lensing, and accretion disks.

---

## Current Features

### Rendering
- OpenGL 3.3 Core Profile
- Phong Lighting
- Mesh Rendering
- Procedural Sphere Generation
- Transform System
- Orbit Camera
- Mouse Zoom
- Double Precision World Coordinates

### Physics
- Newtonian Gravitation
- N-Body Gravity Solver
- Force Accumulation
- Velocity Integration
- Stable Planetary Orbits
- Time Scaling
- SI Unit System

### Simulation
- Universe Management
- Celestial Body System
- Real Astronomical Constants
- Real Planetary Masses
- Real Planetary Radii
- Real Orbital Velocities
- Visual Planet Scaling (independent of physics)

---

## Current Simulation

The engine currently simulates:

- ☀️ Sun
- 🌍 Earth
- ♂️ Mars
- ♃ Jupiter

Each body uses real astronomical values for:

- Mass
- Radius
- Orbital Distance
- Orbital Velocity

---

## Project Structure

```
Physics Engine
│
├── Physics
│   ├── Universe
│   ├── CelestialBody
│   └── GravitySolver
│
├── Rendering
│   ├── Mesh
│   ├── Renderable
│   ├── Camera
│   ├── Shader
│   └── Transform
│
└── Utilities
    └── Constants
```

---

## Technologies Used

- C++
- OpenGL
- GLFW
- GLEW
- GLM

---

## Roadmap

### Engine Architecture
- [x] Universe class
- [x] CelestialBody class
- [x] Gravity solver
- [x] Transform system
- [x] Orbit camera
- [x] Visual scaling
- [ ] SolarSystemFactory
- [ ] Renderer abstraction

### Rendering
- [x] 3D sphere rendering
- [x] Lighting
- [ ] Planet textures
- [ ] Skybox
- [ ] Orbit trails
- [ ] Atmospheric rendering

### Physics
- [x] Newtonian gravity
- [x] SI unit system
- [x] Stable circular orbits
- [ ] Velocity Verlet integration
- [ ] Collision detection
- [ ] Planet merging
- [ ] Adaptive timestep

### Astronomy
- [ ] Complete Solar System
- [ ] Moon system
- [ ] Asteroid belt
- [ ] Comets
- [ ] Artificial satellites

### Future Goals
- [ ] Black hole simulation
- [ ] Schwarzschild metric
- [ ] Gravitational lensing
- [ ] Accretion disks
- [ ] Time dilation
- [ ] Binary black holes

---

## Why SI Units?

All physics calculations use real-world SI units:

- Distance → meters
- Mass → kilograms
- Time → seconds
- Velocity → meters/second

This allows the engine to simulate realistic orbital mechanics while using a separate rendering scale for visualization.

---

## Current Status

The engine has successfully transitioned from a rendering project into a simulation framework with a clean separation between rendering and physics. The current focus is improving engine architecture, visualization tools, and expanding the astrophysics simulation.

---

## License

This project is licensed under the MIT License.
