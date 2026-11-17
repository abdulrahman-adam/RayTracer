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

# Core library: all engine code lives here so the app and tests share it.
add_library(raytracer_core
    src/greeting.cpp
    src/math/vector.cpp
)
target_include_directories(raytracer_core PUBLIC include)
target_link_libraries(raytracer_core PRIVATE raytracer_warnings)

# Executable: a thin entry point over the core library.
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core raytracer_warnings)

if(RAYTRACER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
