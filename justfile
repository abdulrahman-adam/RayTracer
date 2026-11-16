# Shortcuts for the CMake presets (see ADR 0004). Run `just` to list them.

set windows-shell := ["powershell.exe", "-NoLogo", "-NoProfile", "-Command"]

# Build type: debug or release. Override with `just preset=release <command>`.
preset := "debug"

# List the available commands
default:
    @just --list

# Configure and compile
build:
    cmake --preset {{preset}}
    cmake --build --preset {{preset}}

# Build, then run the renderer
start: build
    ./build/{{preset}}/raytracer

# Build, then run the unit tests
test: build
    ctest --preset {{preset}}

# Delete all build output
clean:
    cmake -E rm -rf build
