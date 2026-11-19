#pragma once

#include "material/material.hpp"
#include "math/vector.hpp"

// What we learn when a ray hits an object: where it hit, which way the
// surface faces there, and the material to shade it with.
struct HitInfo {
    // The point on the surface where the ray hit.
    Vector point;

    // The surface normal at `point`: length 1, pointing out of the object.
    Vector normal;

    // The material of the object that was hit. It is not owned: the object
    // keeps it alive, so a HitInfo must not outlive the object it came from.
    const Material* material;
};
