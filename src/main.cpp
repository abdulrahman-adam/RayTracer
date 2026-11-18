#include <iostream>

#include "greeting.hpp"
#include "ray/ray.hpp"
#include "geometry/sphere.hpp"

int main()
{
    std::cout << raytracer::greeting() << '\n';
    raytracer::Ray ray(raytracer::Vector(0, 0, -1), raytracer::Vector(0, 0, 1.0));

    raytracer::Sphere sphere(raytracer::Vector(0, 0, 9), 5);

    bool hit = sphere.hit(ray);
    if(hit)
    {
        std::cout<< "Ray hit the shpere!\n";
    }
    else
    {
        std::cout<< "Ray missed the shpere!\n";
    }
    return 0;
}
