# MinecraftCPP — next steps

## Current state

Working: CMake + Makefile, GLFW window, OpenGL 3.3 core context via GLEW, sky-blue
clear, Escape quits. Layers: `src/main.cpp` -> `src/core/Window`.

Stack: GLFW + GLEW + GLM + OpenGL 3.3 core, all from Fedora repos.
See `docs/SETUP_FEDORA.md`.

## Rules for every milestone

- Each milestone ends compiling, running, and visually verifiable. No half-finished layer.
- Dependencies point one way: `main` -> `core` / `render` / `world` / `player`.
  `core` and `render` never include `world` or `player`.
- Create a directory when its first real class lands, not in advance.
- One shortcut allowed per milestone, marked with a `shortcut:` comment naming the ceiling.
- Do not start milestone N+1 before milestone N is playable.

---

## Milestone 2 — shaders, mesh, camera, one cube

Following [learnopengl Shaders](https://learnopengl.com/Getting-started/Shaders),
then [Transformations](https://learnopengl.com/Getting-started/Transformations) and
[Camera](https://learnopengl.com/Getting-started/Camera).

### 2a — triangle + mesh  [done]

`render/Shader` (compile, link, throw with the info log, RAII, non-copyable) and
`render/Mesh` (VAO + VBO, positions only, `draw()`). `main` draws one triangle with
identity matrices. Builds and runs.

### 2b — uniforms and the shader class review

Chapter material: `uniform` in GLSL, `glGetUniformLocation`, `glUniform*`, the
`setBool/setInt/setFloat` helpers.

Steps:

1. Add `setVec3` to `Shader` for `uColor`. Without it the triangle stays black
   because an unset `vec3` uniform reads as `(0,0,0)`.
2. Decide on a uniform cache. The tutorial queries the location on every `set`
   call. That is fine for one triangle and wrong for 1000 chunks. Add a
   `std::unordered_map<std::string, GLint>` only when the draw count makes it hurt;
   a shortcut comment marks the decision either way.
3. Read the tutorial's shader class and note where ours differs:
   - header-only vs `.hpp` + `.cpp` — split, so a header edit does not recompile the world
   - prints to `stdout` and continues vs throws — throw, a broken program draws nothing
   - no destructor vs `glDeleteProgram` — RAII
   - copyable vs deleted copy — two owners of one GL id means a double delete
4. Do the chapter's exercises: upside-down triangle, horizontal offset uniform,
   pass `aPos` to the fragment shader as a varying.

### 2c — vertex colors, interleaved attributes

Chapter material: `in`/`out` varyings, `layout(location = N)`, stride and offset.

Steps:

1. Vertex becomes 6 floats: `x y z r g b`.
2. Vertex shader gains `layout(location = 1) in vec3 aColor`, outputs
   `out vec3 ourColor`.
3. Fragment shader reads `in vec3 ourColor`.
4. `glVertexAttribPointer(0, 3, ..., 6 * sizeof(float), nullptr)` and
   `glVertexAttribPointer(1, 3, ..., 6 * sizeof(float), (void*)(3 * sizeof(float)))`.
5. `Mesh` grows a second attribute. Keep the stride as a named constant, not a
   repeated literal — the same number now appears in three places.

### 2d — depth, camera, one cube

Files to create:

```
src/render/Camera.hpp/.cpp    position + yaw/pitch -> view and projection matrices
```

Steps:

1. `Camera` holds position, yaw, pitch. `view()` uses `glm::lookAt`, `projection(aspect)`
   uses `glm::perspective(glm::radians(70.0f), aspect, 0.1f, 1000.0f)`.
2. Cube: 36 vertices, 36 indices, EBO in `Mesh`.
3. `glEnable(GL_DEPTH_TEST)` and `glEnable(GL_CULL_FACE)` once after context creation.
4. WASD + mouse look, free-fly, no collision.

**Done when:** the cube has correct depth, back faces are culled, and you can orbit it.

Gotchas: `Window::clear()` should move to a render-side call once `render/` owns drawing.
No fixed-function calls (`glBegin`, `glMatrixMode`) work in a core profile. An unset
matrix uniform is a zero matrix, which collapses every vertex to `w = 0` — silent black
screen. Bind the program before setting uniforms; `glUniform*` writes to the current one.

---

## Milestone 3 — Chunk + Mesher

**Goal:** one 16x16x16 chunk of blocks renders, with hidden faces culled.

Files:

```
src/world/Block.hpp            enum class BlockId : uint8_t { Air, Stone, Dirt, Grass }
src/world/Chunk.hpp/.cpp       fixed 16^3 block array
src/world/Mesher.hpp/.cpp      Chunk -> vertices + indices
```

Steps:

1. `Chunk` holds `std::vector<uint8_t> blocks_` of size 4096 and a static constexpr
   `kSize = 16`. Index as `x + z * 16 + y * 256`.
2. `Chunk::at(x, y, z)` returns `BlockId::Air` when out of bounds, so the mesher needs
   no special cases at chunk edges for now.
3. `Mesher::build(const Chunk&)` loops every block, and for each of the 6 face
   directions emits a quad only if the neighbour is `Air`. 4 vertices + 6 indices per
   face. Vertex = position + normal (or a face id).
4. Build the mesh once after generation, store it next to the chunk. Never rebuild per
   frame.

**Done when:** a chunk renders and the vertex count drops by roughly half compared to
emitting all 6 faces for every solid block (log both numbers once).

`shortcut: naive per-face meshing, ~6x vertex count of greedy meshing, upgrade at milestone 7`

Gotcha: winding order must match `GL_CULL_FACE` (`GL_BACK`, `GL_CCW`). If faces vanish,
flip one quad's index order before touching anything else.

---

## Milestone 4 — World + terrain generation

**Goal:** fly over a few hundred chunks of rolling terrain at 60 fps.

Files:

```
src/world/World.hpp/.cpp      map of chunks, owns meshes, draw loop
src/world/Noise.hpp/.cpp      integer hash -> 2D value noise, 2-3 octaves
```

Steps:

1. `World` keys chunks by integer chunk coordinate (a small hash on `glm::ivec2`).
2. `Noise` is ~40 lines: hash integers to [0,1], bilinear interpolate, sum octaves.
   No noise library.
3. Generate a height per column, fill stone below, dirt for the top three, grass on top.
4. Load and draw chunks in a radius (start with 6).
5. Draw all chunks with the same shader, one `model` matrix per chunk.

**Done when:** terrain has no gaps or seam artifacts and the frame rate is stable.

Gotchas: world coordinates go negative — use floor division for chunk coords, not C++
`/`. Chunk-local coordinate is `world - chunkCoord * 16`, and negative results need
`((x % 16) + 16) % 16`, not `%` alone.

---

## Milestone 5 — Textures

**Goal:** grass has a different top, side, and bottom.

Files:

```
external/stb_image.h           single header, vendored
src/render/Texture.hpp/.cpp
assets/textures/atlas.png      16x16 tiles in a grid
```

Steps:

1. Load the atlas with `stb_image`, upload with `glTexImage2D`.
2. `GL_NEAREST` min/mag filter, mipmaps optional. Blocky look is intended.
3. Add a `uv` vertex attribute; the mesher emits atlas UVs per face.
4. Map block id + face to an atlas tile, then to UV coordinates.

**Done when:** grass top is green, sides are dirt+green, bottom is dirt, with no texture
bleeding between tiles.

Gotcha: bleeding at tile edges. Pad the atlas or inset UVs by half a texel.

---

## Milestone 6 — Player

**Goal:** walk, jump, collide, break and place blocks.

Files:

```
src/player/Player.hpp/.cpp     position, velocity, AABB, physics, raycast
```

Steps:

1. AABB 0.6 x 1.8 x 0.6. Gravity, jump impulse, ground check.
2. Resolve collision per axis, in the order Y then X then Z, against solid blocks.
3. Mouse look with `glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED)`.
4. Raycast with a voxel DDA up to 6 blocks. Left click breaks, right click places
   against the hit face normal.
5. On a block edit, rebuild only the touched chunk's mesh, plus the neighbour chunk
   when the edit sits on a border.

**Done when:** you cannot walk through terrain, and breaking a block updates the mesh
in the same frame.

`shortcut: full chunk rebuild per edit, O(4096) per click, upgrade to per-section rebuilds if bulk edits appear`

Gotcha: rebus the border neighbour or you get a visible hole where two chunks meet.

---

## Milestone 7 — Performance

**Goal:** draw a large view distance without dropping frames. Measure first.

In rough order of payoff:

1. Frustum culling: extract 6 planes from the view-projection matrix, test each chunk's
   AABB. Cheap, removes most draw calls.
2. Greedy meshing in `Mesher`, replacing the milestone 3 shortcut.
3. Chunk generation and meshing on worker threads; upload to GL on the main thread only.
4. Only then consider batching chunk draws into one buffer, or indirect drawing.

Add a frame-time log before and after each step, so the gain is real and not assumed.

---

## Not now

Skip all of this until the milestones above are playable:

- ECS, entities, mobs, inventory, crafting, UI, day/night, weather
- save/load, networking, multiplayer
- engine abstraction layers, plugin systems, config files
- OpenGL 4.x features, compute shaders, shadows, post-processing
- a `Timer` class, an `Input` class, an `Application` class — add only when a second
  caller needs them

## Optional housekeeping

- `git init` and commit at the end of each milestone. The project is not a repo yet.
- Keep `compile_commands.json` symlinked for `clangd` (see setup doc).
