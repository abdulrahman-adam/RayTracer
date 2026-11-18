#include <iostream>

#include "greeting.hpp"
#include "ray/ray.hpp"
#include "camera/camera.hpp"
#include "colour/colour.hpp"
#include "geometry/sphere.hpp"

using raytracer::Camera;
using raytracer::Colour;
using raytracer::Ray;
using raytracer::Sphere;

int main()
{
    std::cout << raytracer::greeting() << '\n';
    Sphere sphere(raytracer::Vector(0, 0, 9), 5);

    Camera camera(raytracer::Vector(0, 0, 1));
    Ray ray = camera.rayThroughCenter();

    Colour colour(0, 0, 0);

    bool hit = sphere.hit(ray);
    if(hit)
    {
        colour = Colour(1, 0, 5);
    }
    std::cout << "Colour: (" << colour.r() << "," << colour.g() << "," << colour.b() << ")\n";

    
    return 0;
}
