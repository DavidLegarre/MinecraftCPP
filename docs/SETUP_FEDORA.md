# Fedora setup

Tested on Fedora 44, g++ 16.2.1, CMake 4.3.

## Dependencies

Everything comes from the official repos. No vendored code, no FetchContent.

```bash
sudo dnf install -y gcc-c++ cmake make glfw-devel glew-devel glm-devel mesa-libGL-devel
```

| Package | Provides |
|---|---|
| `gcc-c++` | C++ compiler |
| `cmake`, `make` | build system |
| `glfw-devel` | window, input, OpenGL context |
| `glew-devel` | OpenGL function loader (GL 3.3 core) |
| `glm-devel` | header-only math (vectors, matrices) |
| `mesa-libGL-devel` | OpenGL development headers |

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

Or use the `Makefile` wrapper at the project root:

```bash
make            # configure + build (default)
make run        # build + launch
make rebuild    # clean + build
make clean
make BUILD_TYPE=Release
```

## Run

```bash
./build/minecraft
```

## Rebuild after editing source

```bash
cmake --build build -j   # or: make
```

`CMakeLists.txt` globs `src/**/*.cpp` with `CONFIGURE_DEPENDS`, so new source
files are picked up without re-running `cmake -S`.

## Project layout

```
src/
  main.cpp        entrypoint: create window, run loop
  core/           platform layer: window, input, timing
  render/         GL layer: shaders, meshes, textures, camera   (milestone 2+)
  world/          game data: blocks, chunks, world gen, mesher  (milestone 3+)
  player/         player state: camera control, physics         (milestone 6+)
```

Layers point one way only: `main` -> `core`/`render`/`world`/`player`.
`core` depends on nothing inside the project. Include as `"core/Window.hpp"`;
`src` is on the include path.

Directories are created when their first real class lands, not in advance.

## Troubleshooting

`glewInit failed: Missing GLX display` (or error code 4) on a Wayland session:
GLEW 2.2.0 loads GL only through GLX, but GLFW defaults to the EGL backend on
Wayland. `src/main.cpp` calls `glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11)`
to force X11 (XWayland). Native Wayland would require switching the loader to
GLAD.

## Tooling (optional)

`clangd` / editor completion reads `build/compile_commands.json`. Enable it with:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ln -sf build/compile_commands.json compile_commands.json
```
