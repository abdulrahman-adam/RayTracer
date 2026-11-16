# 5. Use GitHub Actions to build and test pull requests in the dev container

## Context

The project is preparing for outside contributions. Maintainers need to know that every pull request builds and passes the tests before reviewing it, in the same environment contributors use (the dev container, see ADR 0001) and with the same commands (the CMake presets, see ADR 0002, and GoogleTest through CTest, see ADR 0003).

The repository is hosted on GitHub.

> **TODO: other CI services the maintainers compared, if any.**

## Decision

We use GitHub Actions, with the workflow in `.github/workflows/ci.yml`.

- It runs on every pull request.
- It runs on the `ubuntu-24.04` GitHub-hosted runner.
- The [`devcontainers/ci`](https://github.com/devcontainers/ci) action (`v0.3`) builds the image from `.devcontainer/` and runs the build and tests inside it. The image is not pushed to any registry (`push: never`).
- The command is `cmake --workflow --preset debug`, which configures, builds and runs the whole test suite.
- The workflow only has read access to the repository contents.

## Status

Proposed

## Consequences

- A pull request shows a pass or fail result for the build and the tests, in the same toolchain as the dev container.
- The dev container image is rebuilt on every run, because nothing is cached. This makes runs slower. The apt packages are not pinned (see ADR 0001), so a run can pick up newer tool versions than a contributor's local container.
- Only the `debug` preset with the container's default compiler (GCC) is tested. Clang, `release` and native Windows/MSVC builds are not checked by CI.
- Each run downloads GoogleTest (see ADR 0003), so CI needs network access to GitHub.
- CI does not block merging by itself. Making the check required is a repository setting that the maintainers would have to turn on.
- The project depends on GitHub Actions and on the third-party `devcontainers/ci` action.
