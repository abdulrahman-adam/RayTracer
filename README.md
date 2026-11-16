# RayTracer

**A Modern, Modular and High-Performance Ray Tracing Engine in C++**

RayTracer is an open-source 3D rendering engine written in C++. Its goal is to produce realistic images by simulating the physical behavior of light as it interacts with objects in a virtual 3D environment.

The project focuses on software engineering excellence, performance, modularity, maintainability and extensibility.

## Getting Started

The project is built with **CMake** (3.25+) and **Ninja**, using a C++20 compiler. Build settings are stored in [`CMakePresets.json`](CMakePresets.json), so every editor and platform uses the same configure, build and test commands.

### Option A — Dev container (recommended, any OS)

A [dev container](https://containers.dev/) gives every contributor the same Linux toolchain: GCC, Clang, CMake, Ninja, GDB, clangd, clang-format and `just`. You only need [Docker](https://www.docker.com/products/docker-desktop/) on your machine.

- **VS Code:** install the *Dev Containers* extension, open the folder, then run **Dev Containers: Reopen in Container**. The CMake Tools extension picks up the presets automatically.
- **Zed:** open the folder; when Zed detects `.devcontainer/devcontainer.json`, accept the prompt to open it in the container. Alternatively run the [Dev Container CLI](https://github.com/devcontainers/cli) yourself: `devcontainer up --workspace-folder .` then `devcontainer exec --workspace-folder . bash`.

The first time the container is created, it configures the `debug` build automatically.

### Option B — Native toolchain

Install a C++20 compiler, CMake ≥ 3.25 and Ninja, plus [`just`](https://github.com/casey/just) for the short commands:

| OS      | Install                                                                                          |
|---------|--------------------------------------------------------------------------------------------------|
| Linux   | `sudo apt install build-essential cmake ninja-build just` (or your distro's equivalent)            |
| macOS   | `xcode-select --install` then `brew install cmake ninja just`                                     |
| Windows | Visual Studio 2022 with *Desktop development with C++* (includes CMake and Ninja), then `winget install Casey.Just`. Run the commands from a *Developer PowerShell for VS*: a normal PowerShell does not find `cmake`. |

### Build and run the Hello World demo

From the repository root, use the shortcuts from the [`justfile`](justfile):

| Command      | What it does                                   |
|--------------|------------------------------------------------|
| `just build` | Configure and compile                          |
| `just start` | Build, then run the renderer                   |
| `just test`  | Build, then run the unit tests                 |
| `just clean` | Delete the `build/` folder                     |
| `just`       | List the commands                              |

They use the `debug` build by default. Add `preset=release` for an optimised build, for example `just preset=release start`.

> There is no `make`: the commands start with `just`.

Without `just`, run the CMake commands directly:

```sh
cmake --preset debug          # configure (downloads GoogleTest on the first run)
cmake --build --preset debug  # compile
./build/debug/raytracer       # run  (Windows: .\build\debug\raytracer.exe)
```

Expected output:

```
Hello, World!
```

Use `release` instead of `debug` for an optimised build in `build/release/`.

## Testing and TDD

Unit tests use **[GoogleTest](https://google.github.io/googletest/)**. CMake downloads a pinned release (v1.17.0) automatically, so you don't need to install it.

Run the whole suite:

```sh
just test
```

Without `just`:

```sh
cmake --build --preset debug && ctest --preset debug
```

Or configure, build and test in one command:

```sh
cmake --workflow --preset debug
```

Useful options: `ctest --preset debug -R Greeting` runs only the tests whose names match a pattern, and `./build/debug/tests/raytracer_tests --gtest_filter='Greeting.*'` runs the test binary directly.

### TDD workflow (red → green → refactor)

1. **Red:** write a test that describes the behaviour you want, in `tests/<feature>_test.cpp`:

   ```cpp
   #include <gtest/gtest.h>
   #include "raytracer/vec3.hpp"

   TEST(Vec3, AddsComponentWise)
   {
       const raytracer::Vec3 a{1, 2, 3};
       const raytracer::Vec3 b{4, 5, 6};
       EXPECT_EQ(a + b, (raytracer::Vec3{5, 7, 9}));
   }
   ```

   Add a new test file to the list in [`tests/CMakeLists.txt`](tests/CMakeLists.txt). Build and run the tests and watch this one fail (or fail to compile).
2. **Green:** write just enough code in `include/raytracer/` and `src/` to make the test pass. Add any new `.cpp` file to `raytracer_core` in the root [`CMakeLists.txt`](CMakeLists.txt).
3. **Refactor:** tidy up the code while all tests stay green.

Repeat in small steps. Commit when the tests pass.

### Project layout

```
.devcontainer/        Docker-based development environment
include/raytracer/    Public headers of the engine
src/                  Engine sources (raytracer_core library) and main.cpp
tests/                GoogleTest unit tests (raytracer_tests)
CMakeLists.txt        Build definition
CMakePresets.json     Shared configure/build/test presets
justfile              Short commands: just build / start / test / clean
docs/adr/             Architecture decision records
.github/              CI workflow, pull request and issue templates
```

All engine code goes into the `raytracer_core` library. Both the `raytracer` executable and the test binary link against it, so any engine code can be tested directly. `main.cpp` stays a thin entry point.

## Project Vision

The vision is to build a reliable and extensible ray tracing engine that can evolve into a powerful rendering solution.

Rather than focusing only on producing images, this project emphasizes building high-quality software through clean architecture, well-designed abstractions, automated testing and performance optimization.

## Planned Features

- **Ray Casting:** Generate rays from a virtual camera into a 3D scene.
- **3D Geometry:** Support objects such as spheres, planes and other geometric primitives.
- **Lighting:** Simulate realistic light sources and illumination.
- **Shadows:** Calculate shadows based on light and object intersections.
- **Reflections:** Simulate reflective surfaces and recursive ray tracing.
- **Materials:** Support different surface properties and materials.
- **Camera System:** Configure camera position, orientation and field of view.
- **Rendering:** Generate rendered images from 3D scenes.
- **Performance:** Explore optimization techniques and parallel processing.
- **Testing:** Build a reliable automated testing system.

## Technical Goals

The project follows modern software engineering principles:

- SOLID principles
- DRY (Don't Repeat Yourself)
- Object-Oriented Programming
- Clean Code and modular architecture
- Separation of concerns
- Automated testing
- Performance profiling and optimization
- Technical documentation

## Technology Stack

- **Language:** C++20
- **Build System:** CMake + Ninja (with CMake presets), `just` for short commands
- **Development Environment:** Dev container (Docker)
- **Version Control:** Git
- **Testing:** GoogleTest
- **Continuous Integration:** GitHub Actions, in the dev container
- **Documentation:** Markdown, with Architecture Decision Records in [`docs/adr/`](docs/adr/)

## Architecture

The engine is designed around independent and reusable components.

Potential modules include:

- `Core` – Main rendering engine and application logic.
- `Math` – Vectors, matrices and mathematical operations.
- `Geometry` – 3D objects and ray intersection algorithms.
- `Materials` – Surface properties and material models.
- `Lighting` – Light sources and illumination calculations.
- `Camera` – Camera configuration and ray generation.
- `Renderer` – Rendering pipeline and image generation.
- `Tests` – Unit and integration tests.

## Open Source

This project is developed as an open-source initiative.

Contributions, suggestions, bug reports and improvements are welcome.

Whether you are interested in computer graphics, C++, software architecture or rendering optimization, you are welcome to participate.

- [CONTRIBUTING.md](CONTRIBUTING.md): set up the dev container, build and test, work test-first, use the ADRs and submit a pull request.
- [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md): the behaviour we expect from everyone in the community.
- [Architecture Decision Records](docs/adr/): the decisions behind the build, tools and test setup.

## Project Status

🚧 Under active development.

Features and architecture may evolve as the project progresses.

## License

This project is released under the MIT License. See the [`LICENSE`](LICENSE) file for details.

---

**Built with C++ | Open Source | Made for Computer Graphics and Software Engineering**
