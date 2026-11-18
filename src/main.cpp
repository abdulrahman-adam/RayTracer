#include <iostream>

#include "greeting.hpp"
#include "camera/camera.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"
#include "math/vector.hpp"

using raytracer::Camera;
using raytracer::Image;
using raytracer::PngSaver;
using raytracer::Sphere;
using raytracer::Vector;

int main()
{
    std::cout << raytracer::greeting() << '\n';

    const int imageWidth = 512;
    const int imageHeight = 512;

    Sphere sphere(Vector(0, 0, 9), 5);
    Camera camera(Vector(0, 0, -1), 2.0);
    Image image(imageWidth, imageHeight);

    camera.render(sphere, image);

    PngSaver saver;
    saver.save(image, "output.png");
    std::cout << "Saved output.png (" << imageWidth << "x" << imageHeight << ")\n";

    return 0;
}
