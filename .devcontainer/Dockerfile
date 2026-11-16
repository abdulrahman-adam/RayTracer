FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

# C++ toolchain: GCC and Clang, CMake + Ninja, debugger and formatting tools,
# and the `just` command runner for the build shortcuts (see ADR 0004).
RUN apt-get update \
    && export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        clang-format \
        clang-tidy \
        clangd \
        cmake \
        gdb \
        just \
        ninja-build \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
