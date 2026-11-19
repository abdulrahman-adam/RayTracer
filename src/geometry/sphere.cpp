#include "ray/ray.hpp"
#include "geometry/sphere.hpp"
#include <cmath>
#include <utility>

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material)
    : _center(center), _radius(radius), _material(std::move(material))
{
}

const Vector& Sphere::center() const
{
    return _center;
}

double Sphere::radius() const
{
    return _radius;
}

const Material& Sphere::material() const
{
    return *_material;
}

std::optional<HitInfo> Sphere::hit(const Ray& ray) const
{
    Vector D = ray.direction();
    Vector O = ray.origin();
    Vector C = _center;

    Vector L = O - C;
    double a = D.dot(D);
    double b = 2*D.dot(L);
    double c = L.dot(L) - _radius*_radius;

    double delta = b*b - 4*a*c;

    if(delta < 0)
    {
        return std::nullopt;
    }

    // a > 0, so t2 <= t1: t2 is the nearer of the two intersections.
    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);

    double t;
    if(t2 >= 0)
    {
        t = t2;
    }
    else if(t1 >= 0)
    {
        t = t1; // The ray starts inside the sphere.
    }
    else
    {
        return std::nullopt; // The sphere is behind the ray.
    }

    Vector point = ray.at(t);
    Vector normal = (point - C).normalised();
    return HitInfo{point, normal, _material.get()};
}
