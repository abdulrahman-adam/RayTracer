#pragma once

#include "colour/colour.hpp"
#include "ray/ray.hpp"
#include "scene/scene.hpp"

// The colour seen along `ray` in `scene`: the nearest shape the ray hits,
// shaded by that shape's material with the hit and the scene's light.
// A ray that hits nothing gives the background, black.
Colour trace(const Ray& ray, const Scene& scene);
