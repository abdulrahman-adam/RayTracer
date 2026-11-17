# AGENTS.md

C++20 ray tracing engine built with CMake presets and Ninja. Tests use GoogleTest through CTest.

## Commands

Run these from the repository root, either inside the dev container (`.devcontainer/`) or with a native CMake 3.25+ / Ninja / C++20 toolchain. The shortcuts are defined in `justfile`.

```sh
just build    # configure + compile   (cmake --preset debug && cmake --build --preset debug)
just start    # build, then run       (./build/debug/raytracer)
just test     # build, then test      (ctest --preset debug)
just clean    # delete build/
```

Add `preset=release` for an optimised build, e.g. `just preset=release test`. If `just` is not installed, run the CMake commands shown in parentheses.

The `Makefile` gives the same commands with `make` (ADR 0006): `make` / `make build`, `make run`, `make test`, `make clean`, with `preset=release` as an option, e.g. `make test preset=release`.

When you add or rename a CMake preset or a command, update both `justfile` and `Makefile` to match.

## Contributor docs

- `CONTRIBUTING.md`: dev container setup, `just` commands, TDD workflow, ADR process and how to submit a pull request. Keep it in sync when commands, tools or the workflow change.
- `CODE_OF_CONDUCT.md`: Contributor Covenant 2.1.
- `LICENSE`: MIT.
- `.github/workflows/ci.yml`: CI that runs `cmake --workflow --preset debug` in the dev container on every pull request (ADR 0005).
- `.github/PULL_REQUEST_TEMPLATE.md` and `.github/ISSUE_TEMPLATE/`: pull request and issue templates.

## Architecture decisions

- Our architecture decisions are in `docs/adr/`. Read them before changing the build, the tools or the test setup.
- Never go against an accepted ADR. To change a decision, write a new ADR with status **Proposed** and ask the maintainer.
- Never set an ADR's status to **Accepted**. Only the maintainers do that.
