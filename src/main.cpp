#include <iostream>
#include <memory>

#include "camera/camera.hpp"
#include "colour/colour.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"
#include "light/light.hpp"
#include "material/lambert_shader.hpp"
#include "math/vector.hpp"
#include "scene/scene.hpp"

int main()
{
    const int imageWidth = 512;
    const int imageHeight = 512;

    // Describe the scene, lit by a white light above, to the left of and in
    // front of the ball
    Scene scene(Light(Vector(-10, 10, -10), Colour(1.0, 1.0, 1.0)));

    // A yellow ball of radius 5...
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5,
                                       std::make_shared<LambertShader>(Colour(1.0, 1.0, 0.0))));

    // ...resting on a grey floor: the plane y = -5, facing up
    scene.add(std::make_unique<Plane>(Vector(0, -5, 0), Vector(0, 1, 0),
                                      std::make_shared<LambertShader>(Colour(0.8, 0.8, 0.8))));

    // Position and configure the camera
    Camera camera(Vector(0, 0, -1), 2.0);

    Image image(imageWidth, imageHeight);

    // Render the scene into the image
    camera.render(scene, image);

    PngSaver saver;
    saver.save(image, "image.png");
    std::cout << "Saved image.png (" << imageWidth << "x" << imageHeight << ")\n";

    return 0;
}
