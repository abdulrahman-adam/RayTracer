#include <iostream>

#include "greeting.hpp"
#include "ray/ray.hpp"
#include "camera/camera.hpp"
#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"

using raytracer::Camera;
using raytracer::Colour;
using raytracer::Image;
using raytracer::PngSaver;
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


    Image image(800, 600);
    image.setPixel(400,300, colour);

    PngSaver saver;
    saver.save(image, "output.png");
    
    return 0;
}
