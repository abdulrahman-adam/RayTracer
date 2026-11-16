#include <gtest/gtest.h>

#include "raytracer/greeting.hpp"

TEST(Greeting, SaysHelloWorld)
{
    EXPECT_EQ(raytracer::greeting(), "Hello, World!");
}
