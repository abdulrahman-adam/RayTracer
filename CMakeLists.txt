cmake_minimum_required(VERSION 3.25)

project(RayTracer
    VERSION 0.1.0
    DESCRIPTION "A modular ray tracing engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # used by clangd

option(RAYTRACER_BUILD_TESTS "Build the unit tests" ON)

# Warnings applied to our own targets (not to third-party code).
add_library(raytracer_warnings INTERFACE)
if(MSVC)
    target_compile_options(raytracer_warnings INTERFACE /W4 /permissive-)
else()
    target_compile_options(raytracer_warnings INTERFACE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

# LodePNG encodes PNG files (ADR 0007). It is downloaded at configure time,
# pinned to a commit (the project has no release tags) and checked by hash.
# It ships no CMakeLists.txt, so we build its single source file ourselves.
include(FetchContent)
FetchContent_Declare(
    lodepng
    URL https://github.com/lvandeve/lodepng/archive/7b2893e35891c0c85bee5595caafaf3c2044b409.tar.gz
    URL_HASH SHA256=e0b571062acdbe187fd4e8b0ff46f6e7d1b634457ff1a4b383aaac4c78bfd59b
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(lodepng)

add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
# SYSTEM: our strict warnings are not applied to LodePNG's header.
target_include_directories(lodepng SYSTEM PUBLIC ${lodepng_SOURCE_DIR})

# Core library: all engine code lives here so the app and tests share it.
add_library(raytracer_core
    src/greeting.cpp
    src/math/vector.cpp
    src/ray/ray.cpp
    src/geometry/sphere.cpp
    src/camera/camera.cpp
    src/colour/colour.cpp
    src/material/flat_shader.cpp
    src/image/image.cpp
    src/io/png_saver.cpp
)
target_include_directories(raytracer_core PUBLIC src)
target_link_libraries(raytracer_core PRIVATE raytracer_warnings lodepng)

# Executable: a thin entry point over the core library.
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core raytracer_warnings)

if(RAYTRACER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
