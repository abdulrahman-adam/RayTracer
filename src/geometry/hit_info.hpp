#pragma once

#include "material/material.hpp"
#include "math/vector.hpp"

// What we learn when a ray hits an object: where it hit, which way the
// surface faces there, the material to shade it with, and how far along the
// ray the hit is.
struct HitInfo {
    // The point on the surface where the ray hit.
    Vector point;

    // The surface normal at `point`, of length 1. It is the shape's own
    // normal, whichever side the ray comes from: out of the centre for a
    // sphere, the given normal for a plane.
    Vector normal;

    // The material of the object that was hit. It is not owned: the object
    // keeps it alive, so a HitInfo must not outlive the object it came from.
    const Material* material;

    // The ray parameter of the hit: `point` is ray.at(t). It is never
    // negative. With a non-unit ray direction it is not a distance, but for
    // hits on the same ray a smaller t is always a nearer hit, which is what
    // Scene::nearestHit compares.
    double t;
};
