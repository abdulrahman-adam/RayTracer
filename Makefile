# Short `make` commands for the CMake presets (see ADR 0006).
# They run the same commands as the justfile. Run `make help` to list them.

# Build type: debug or release. Override with `make test preset=release`.
preset ?= debug

ifeq ($(OS),Windows_NT)
  # Use cmd.exe, and load the Visual Studio build tools (cmake, ninja, MSVC)
  # so the commands also work from a normal PowerShell.
  SHELL := cmd.exe
  VSENV := scripts\vsenv.cmd
  RAYTRACER := build\$(preset)\raytracer.exe
else
  VSENV :=
  RAYTRACER := ./build/$(preset)/raytracer
endif

.DEFAULT_GOAL := build
.PHONY: build run test clean help

# Configure and compile
build:
	$(VSENV) cmake --preset $(preset)
	$(VSENV) cmake --build --preset $(preset)

# Build, then run the renderer
run: build
	$(RAYTRACER)

# Build, then run the unit tests
test: build
	$(VSENV) ctest --preset $(preset)

# Delete all build output
clean:
	$(VSENV) cmake -E rm -rf build

# List the commands
help:
	@echo make build   - Configure and compile (default)
	@echo make run     - Build, then run the renderer
	@echo make test    - Build, then run the unit tests
	@echo make clean   - Delete all build output
	@echo Add preset=release for an optimised build, e.g. make test preset=release
