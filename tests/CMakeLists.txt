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
    greeting_test.cpp
)
target_link_libraries(raytracer_tests PRIVATE raytracer_core raytracer_warnings GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(raytracer_tests)
