include(FetchContent)

# GoogleTest is downloaded at configure time, pinned to a release.
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# On Windows/MSVC, use the same runtime library as the rest of the project.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add new test files to this list.
add_executable(raytracer_tests
    math/vector_test.cpp
    ray/ray_test.cpp
    geometry/sphere_test.cpp
    geometry/plane_test.cpp
    scene/scene_test.cpp
    trace/trace_test.cpp
    camera/camera_test.cpp
    colour/colour_test.cpp
    material/flat_shader_test.cpp
    material/lambert_shader_test.cpp
    light/light_test.cpp
    image/image_test.cpp
    io/png_saver_test.cpp
)
# So every test file can include the shared test_helpers.hpp.
target_include_directories(raytracer_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# lodepng: the PNG tests decode saved files to check their pixels.
target_link_libraries(raytracer_tests PRIVATE raytracer_core raytracer_warnings lodepng GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(raytracer_tests)
