# 1. Use a dev container for the development environment

## Context

Contributors need a C++20 toolchain (compiler, CMake, Ninja, debugger, formatting tools) to build and test the engine.

> **TODO: board's reason for choosing a dev container.**

Alternatives in this repository:

- **Native toolchain on each machine.** Still documented as README "Option B": `build-essential`/Xcode/Homebrew on Linux and macOS, Visual Studio 2022 on Windows. Each contributor installs and maintains their own versions.

## Decision

We provide a Docker-based dev container in `.devcontainer/` and recommend it as the default environment.

- Base image: `mcr.microsoft.com/devcontainers/base:ubuntu-24.04`.
- Installed tools: GCC (`build-essential`), Clang, clang-format, clang-tidy, clangd, CMake, Ninja and GDB.
- VS Code gets the C/C++, CMake Tools and clangd extensions, and is set to always use the CMake presets.
- `postCreateCommand` runs `cmake --preset debug`, so the project is configured the first time the container is created.

The native toolchain stays documented as a supported alternative.

## Status

Proposed

## Consequences

- Every contributor using the container gets the same Linux toolchain, whatever their host OS.
- Docker is required to use the container.
- The apt packages are not pinned to versions. Rebuilding the image later can pick up newer compilers or tools from Ubuntu 24.04.
- The container only builds with GCC/Clang on Linux. The MSVC branch in `CMakeLists.txt` (`/W4 /permissive-`) is only exercised by native Windows builds.
- Two supported setups (container and native) have to be kept working and documented.
- The container and a native build write to the same `build/<preset>` folders. Switching between them requires deleting the folder, because CMake will not reuse a cache from a different toolchain.
