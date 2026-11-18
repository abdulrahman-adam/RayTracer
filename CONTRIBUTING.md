# Contributing to RayTracer

Thank you for your interest in RayTracer! This guide explains how to set up the project, build it, run the tests and submit a change.

By taking part in this project, you agree to follow our [Code of Conduct](CODE_OF_CONDUCT.md). Contributions are accepted under the project's [MIT License](LICENSE).

## 1. Set up the dev container

The recommended environment is the dev container in [`.devcontainer/`](.devcontainer/) (see [ADR 0001](docs/adr/0001-dev-container.md)). It gives everyone the same Linux toolchain: GCC, Clang, CMake, Ninja, GDB, clangd, clang-format, clang-tidy and `just`.

You only need [Docker](https://www.docker.com/products/docker-desktop/) and Git on your machine.

1. Fork the repository on GitHub and clone your fork.
2. Open the folder in the container:
   - **VS Code:** install the *Dev Containers* extension, open the folder, then run **Dev Containers: Reopen in Container**.
   - **Zed:** open the folder and accept the prompt to open it in the container.
   - **Any editor:** use the [Dev Container CLI](https://github.com/devcontainers/cli): `devcontainer up --workspace-folder .` then `devcontainer exec --workspace-folder . bash`.
3. The first time the container is created, it configures the `debug` build automatically.

You can also build with a native toolchain (a C++20 compiler, CMake 3.25+ and Ninja). See *Option B* in the [README](README.md#option-b--native-toolchain). If you switch between the container and a native build, delete the `build/` folder first, because CMake will not reuse a cache from a different toolchain.

## 2. Build, run and test

The [`justfile`](justfile) gives short commands for the CMake presets (see [ADR 0002](docs/adr/0002-cmake.md) and [ADR 0004](docs/adr/0004-just-command-runner.md)). `just` is installed in the dev container. Run `just` on its own to list the commands.

| Command      | What it does                                   |
|--------------|------------------------------------------------|
| `just build` | Configure and compile                          |
| `just start` | Build, then run the renderer                   |
| `just test`  | Build, then run the unit tests                 |
| `just clean` | Delete all build output                        |

They use the `debug` preset by default. Add `preset=release` for an optimised build, for example `just preset=release test`.

The [`Makefile`](Makefile) gives the same commands with `make` (see [ADR 0006](docs/adr/0006-makefile-shortcuts.md)): `make build` (or just `make`), `make run`, `make test` and `make clean`. `make` is installed in the dev container. Add `preset=release` for an optimised build, for example `make test preset=release`.

If you don't have `just`, use CMake directly:

```sh
cmake --preset debug            # configure (downloads GoogleTest on the first run)
cmake --build --preset debug    # build
ctest --preset debug            # test
cmake --workflow --preset debug # configure + build + test in one step
```

To run only some tests: `ctest --preset debug -R <pattern>`.

## 3. Work test-first (TDD)

We develop in small red → green → refactor steps, with [GoogleTest](https://google.github.io/googletest/) (see [ADR 0003](docs/adr/0003-googletest.md)).

1. **Red:** write a test for the behaviour you want in `tests/<concept>/<feature>_test.cpp` (e.g. `tests/math/vector_test.cpp`). Add new test files to the list in [`tests/CMakeLists.txt`](tests/CMakeLists.txt). Run the tests and watch the new one fail (or fail to compile).
2. **Green:** write just enough code to make it pass. Group files by concept: headers and sources go side by side in `src/<concept>/` (e.g. `src/math/vector.hpp` and `src/math/vector.cpp`). Add new `.cpp` files to `raytracer_core` in the root [`CMakeLists.txt`](CMakeLists.txt).
3. **Refactor:** clean up the code while all tests stay green.

All engine code goes into the `raytracer_core` library, so the tests can use it directly. `src/main.cpp` stays a thin entry point. The project compiles with strict warnings (`-Wall -Wextra -Wpedantic -Wshadow -Wconversion`). Keep your code free of warnings.

See [Testing and TDD](README.md#testing-and-tdd) in the README for a full example.

## 4. Architecture Decision Records (ADRs)

Important decisions about the build, the tools and the test setup are recorded in [`docs/adr/`](docs/adr/). Read them before you change any of these.

- **Follow the accepted ADRs.** Don't make a change that goes against an ADR with status **Accepted**.
- **To make or change a decision,** for example adding a new tool, library or service, write a new ADR with status **Proposed** and include it in your pull request. Don't edit an accepted ADR to change its decision.
- **Only maintainers set an ADR's status to Accepted.**

To write an ADR:

1. Name the file `docs/adr/NNNN-short-title.md`, using the next free number (for example `0006-...`).
2. Start with `# N. Title`, then use these sections, in the same order as the existing ADRs:
   - **Context:** the problem and the constraints, with the alternatives considered.
   - **Decision:** what we do, concretely.
   - **Status:** `Proposed`.
   - **Consequences:** what becomes easier or harder, including the downsides.

## 5. Submit a change

To report a bug or suggest a feature, open an issue with the bug report or feature request template.

1. **Create a branch** in your fork.
2. **Make your change test-first** (section 3), and add an ADR if needed (section 4).
3. **Check locally** that `just test` (or `cmake --workflow --preset debug`) passes inside the dev container.
4. **Open a pull request** against `main` and fill in the template.
5. **CI** builds the project and runs the tests in the dev container on every pull request (see [ADR 0005](docs/adr/0005-github-actions-ci.md)). If it fails, open the *CI* check on your pull request to see the log, fix the problem and push again.
6. A maintainer reviews your pull request.
