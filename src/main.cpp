#include <iostream>

#include "greeting.hpp"
#include "camera/camera.hpp"
#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"
#include "math/vector.hpp"

using raytracer::Camera;
using raytracer::Colour;
using raytracer::Image;
using raytracer::PngSaver;
using raytracer::Sphere;
using raytracer::Vector;

int main()
{
    std::cout << raytracer::greeting() << '\n';

    const int imageWidth = 512;
    const int imageHeight = 512;

    // Describe the scene
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1.0, 1.0, 0.0));

    // Positio and cong=figure the camera
    Camera camera(Vector(0, 0, -1), 2.0);

    Image image(imageWidth, imageHeight);

    // Render the scene into the image 
    camera.render(sphere, image);

    PngSaver saver;
    saver.save(image, "output.png");
    std::cout << "Saved output.png (" << imageWidth << "x" << imageHeight << ")\n";

    return 0;
}
