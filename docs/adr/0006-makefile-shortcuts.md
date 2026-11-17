# 6. Add a Makefile with the same shortcuts as the justfile

## Context

ADR 0004 proposes `just` for the build, run and test shortcuts, and lists a Makefile as a rejected alternative because `make` is not available in a standard Windows PowerShell.

The maintainer wants to type `make`, `make build`, `make run` and `make test` in a terminal, especially inside the dev container. `make` is already installed in the dev container, because it is part of `build-essential` (ADR 0001), so no new tool is needed there.

## Decision

We add a `Makefile` at the repository root next to the `justfile`. It defines:

- `make` / `make build`: configure and compile
- `make run`: build, then run the renderer
- `make test`: build, then run the unit tests with CTest
- `make clean`: delete `build/`
- `make help`: list the commands

The commands default to the `debug` preset. `make <command> preset=release` uses `release`. Like the `justfile`, the `Makefile` only calls the CMake and CTest preset commands (ADR 0002).

The `justfile` stays, so `just` keeps working, including on native Windows without `make`.

## Status

Proposed

## Consequences

- `make build`, `make run` and `make test` work in the dev container with no change to the image.
- On native Windows, `make` has to be installed separately (for example `winget install ezwinports.make`). The `Makefile` then uses `cmd.exe` and runs each command through `scripts/vsenv.cmd`, which finds Visual Studio with `vswhere` and loads its developer environment, so the commands work from a normal PowerShell.
- Two shortcut files (`justfile` and `Makefile`) have to be kept in sync when presets or commands are added or renamed.
- The run command is named `run` in the `Makefile` and `start` in the `justfile`.
