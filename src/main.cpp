#include <iostream>

#include "greeting.hpp"
#include "geometry/ray.hpp"
#include "geometry/sphere.hpp"

int main()
{
    std::cout << raytracer::greeting() << '\n';
    raytracer::Ray ray(raytracer::Vector(0, 0, -1), raytracer::Vector(0, 0, 1.0));

    raytracer::Sphere sphere(raytracer::Vector(0, 0, 9), 5);

    return 0;
}
