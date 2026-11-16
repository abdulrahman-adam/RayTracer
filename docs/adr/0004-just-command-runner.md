# 4. Use `just` for build, run and test shortcuts

## Context

The CMake preset commands (ADR 0002) are long and hard to remember when building, running or testing by hand. Contributors asked for short commands like `npm run build` or `npm run start`. CMake has no equivalent of npm scripts.

Alternatives considered:

- **Two wrapper scripts** (`run.ps1` for Windows, `run.sh` for the container and Unix). No new tool, but every command is written twice.
- **VS Code tasks** (`.vscode/tasks.json`). No new tool, but they only work inside VS Code, not in Zed or a plain terminal.
- **A Makefile.** `make` is not available in a standard Windows PowerShell.

## Decision

We use [`just`](https://github.com/casey/just) as a command runner. A single `justfile` at the repository root defines:

- `just build`: configure and compile
- `just start`: build, then run the renderer
- `just test`: build, then run the unit tests with CTest
- `just clean`: delete `build/`

The commands default to the `debug` preset. `just preset=release <command>` uses `release`. On Windows, `just` runs the commands in PowerShell.

`just` is installed in the dev container (ADR 0001). The `justfile` only calls the CMake and CTest preset commands, so those commands keep working without `just`.

## Status

Proposed

## Consequences

- One short set of commands works on Windows, macOS, Linux and in the dev container.
- Native contributors must install one more tool (for example `winget install Casey.Just` on Windows).
- The container gets `just` from Ubuntu 24.04 (version 1.21.0 at the time of writing). It is not pinned, and may differ from the version installed natively.
- The `justfile` must be kept in sync when presets are added or renamed.
