# 2. Use CMake with presets, Ninja and CTest

## Context

The engine has to be built and tested the same way on Linux, macOS, Windows and in the dev container (see ADR 0001), and from different editors (VS Code, Zed, Visual Studio).

> **TODO: board's reason for choosing CMake.**

> **TODO: other build systems the board compared, if any.** This repository does not mention any alternative build system.

## Decision

We use CMake (minimum 3.25) with the Ninja generator, and CTest to run the tests.

- `CMakePresets.json` (version 6) defines `debug` and `release` configure, build and test presets. Output goes to `build/<preset>`.
- A `debug` workflow preset runs configure, build and test in one command: `cmake --workflow --preset debug`.
- All engine code goes into the `raytracer_core` library. The `raytracer` executable and the test binary both link against it.
- A `raytracer_warnings` interface target applies strict warnings to our own targets only (`-Wall -Wextra -Wpedantic -Wshadow -Wconversion`, or `/W4 /permissive-` on MSVC).
- `CMAKE_EXPORT_COMPILE_COMMANDS` is on, so clangd can index the code.
- Tests are enabled with `enable_testing()` (option `RAYTRACER_BUILD_TESTS`, default ON) and registered with CTest. The test presets print output on failure.

## Status

Proposed

## Consequences

- One set of commands works across editors, operating systems and the dev container.
- CMake 3.25 or newer and Ninja must be installed for native builds. On Windows they come with Visual Studio and must be run from a Developer PowerShell.
- New `.cpp` files and test files must be added by hand to `CMakeLists.txt` and `tests/CMakeLists.txt`.
- There is a workflow preset for `debug` only. Release builds need separate configure, build and test commands.
