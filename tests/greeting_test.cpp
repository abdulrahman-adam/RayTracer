#include <gtest/gtest.h>

#include "greeting.hpp"

TEST(Greeting, SaysHelloWorld)
{
    EXPECT_EQ(raytracer::greeting(), "Hello, World!");
}
