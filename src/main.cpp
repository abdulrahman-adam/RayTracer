#include <iostream>
#include <memory>

#include "greeting.hpp"
#include "camera/camera.hpp"
#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"
#include "light/light.hpp"
#include "material/lambert_shader.hpp"
#include "math/vector.hpp"

int main()
{
    std::cout << greeting() << '\n';

    const int imageWidth = 512;
    const int imageHeight = 512;

    // Describe the scene
    Sphere sphere(Vector(0, 0, 9), 5, std::make_shared<LambertShader>(Colour(1.0, 1.0, 0.0)));

    // A white light above, to the left of and in front of the sphere
    Light light(Vector(-10, 10, -10), Colour(1.0, 1.0, 1.0));

    // Positio and cong=figure the camera
    Camera camera(Vector(0, 0, -1), 2.0);

    Image image(imageWidth, imageHeight);

    // Render the scene into the image 
    camera.render(sphere, light, image);

    PngSaver saver;
    saver.save(image, "output.png");
    std::cout << "Saved output.png (" << imageWidth << "x" << imageHeight << ")\n";

    return 0;
}
