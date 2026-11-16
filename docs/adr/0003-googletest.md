# 3. Use GoogleTest for unit tests

## Context

The project aims for an engine that is tested and easy to extend, and development follows a test-first (red → green → refactor) workflow. We need a C++ unit test framework that integrates with CMake and CTest (see ADR 0002).

> **TODO: board's reason for choosing the test framework.**

Alternatives:

- **Catch2.** It was named as a candidate when these ADRs were requested. The repository does not use it.

> **TODO: confirm why Catch2 was not chosen, and list any other frameworks the board compared.**

## Decision

We use GoogleTest.

- `tests/CMakeLists.txt` downloads GoogleTest v1.17.0 at configure time with `FetchContent`, from a pinned release archive. Nothing has to be installed.
- The `raytracer_tests` executable links `GTest::gtest_main`, `raytracer_core` and the project warnings.
- `gtest_discover_tests` registers each `TEST` with CTest, so `ctest --preset debug -R <pattern>` can select individual tests.
- On MSVC, `gtest_force_shared_crt` makes GoogleTest use the same runtime library as the project.

## Status

Proposed

## Consequences

- Tests run through the same CTest and preset commands as the rest of the build.
- The version is pinned, so every machine tests against the same GoogleTest.
- The first configure needs network access to download GoogleTest.
- GoogleMock is built along with GoogleTest even though no test uses it yet, which adds build time.
- Each new test file must be added by hand to `tests/CMakeLists.txt`.
