# Physics Engine — 3D Solar System Simulator
 
a 3D solar system sim built from scratch in C++ and OpenGL. no game engine, no physics library, i wanted to actually understand how this stuff works instead of just calling a function and trusting it.
 
everything uses real SI units for the physics, and gravity is full n-body, meaning every planet actually pulls on every other planet, not just the sun pulling on planets while they ignore each other. the spheres themselves are procedurally generated too, drawn by looping vertices along latitude and longitude lines instead of loading premade planet meshes.
 
## demo
 
[watch a short demo here](https://www.youtube.com/watch?v=hP4zgpyufLg)
 
![Overview](Images/Overview.png)
 
## installation
 
there's two ways to get this running:
 
**option 1 — just run the prebuilt version (easiest)**
 
1. grab the latest release from the [Releases page](https://github.com/shadowplayzman/physics-engine/releases)
2. unzip it
3. run `physics-engine.exe`
that's it, no separate install needed, glew32.dll and glfw3.dll are already bundled with the release along with the textures and shaders.
 
**option 2 — build it yourself from source**
 
1. clone the repo
```
   git clone https://github.com/shadowplayzman/physics-engine.git
```
2. open `physics-engine.slnx` in Visual Studio (2022 or newer)
3. dependencies (GLFW, GLEW, GLM, Dear ImGui, stb_image) are already vendored in the `external` folder, so there's nothing extra to download
4. set the build config to `Release` and `x64`
5. build and run — the exe will land in the output folder alongside the required dlls
windows only for now, since it's built and tested on 1920x1080 windows (see known issues below).
 
## features
 
- real-time newtonian gravity, full n-body (every body affects every other body)
- procedurally generated spheres (no premade meshes)
- textured planets, saturn rings, skybox
![Earth](Images/Earth.png)
![Saturn](Images/saturn.png)
 
- orbit trails with adjustable length and color
- pause/resume and adjustable simulation speed
- spawn custom planets or ones based on real planet templates
- edit any planet's mass, radius, position, velocity, trail length and color live, mid-simulation
- standalone executable, no install needed
## the UI
 
the whole interface is built with dear imgui, split into 3 windows:
 
**Simulation window** — shows how many bodies are currently in the scene, how much time has passed (in earth years/days/hours), lets you scale simulation speed up or down, pause it, or reset back to the default solar system.
 
![Simulation controls](Images/Simulation.png)
 
**Planet Inspector** — press TAB to cycle through planets (defaults to the sun). shows and lets you edit mass, radius, position, velocity, trail length and trail color for whichever planet is selected. there's also a "preserve density" toggle — turn it on and increasing radius scales mass along with it automatically, turn it off and you can change mass/radius independently.
 
![Planet inspector](Images/Planet_Inspector.png)
 
**Planet Spawner** — spawn new bodies based on templates of the real planets (tweak values if you want), or go full custom and build a body from scratch, then hit spawn.
 
![Planet spawner](Images/Planet_spawner.png)
 
## controls
 
- Left Mouse Button — rotate camera
- Mouse Wheel — zoom
- TAB — switch between planets
most of the actual simulation control happens through the imgui windows, not keybinds.
 
## built with
 
- C++
- OpenGL
- GLFW
- GLEW
- GLM
- Dear ImGui
- stb_image
## known issues
 
- built for 1920x1080, hasn't been adapted for other resolutions/window sizes yet, so UI scaling might look off elsewhere
- saturn's rings look pretty rough, tried to fix them and this is what i landed on for now
## why i built this
 
mainly wanted to stop treating physics/rendering engines like a black box. learning the OpenGL side (matrices, model matrices, translation matrices, all of it) was probably the hardest part of the whole project. this is v1, planning to keep building on it.
 
## found a bug?
 
open an issue, or send a pull request if you want to fix it yourself.
