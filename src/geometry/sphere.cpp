#include "ray/ray.hpp"
#include "geometry/sphere.hpp"
#include <cmath>

namespace raytracer {

Sphere::Sphere(const Vector& center, double radius)
    : _center(center), _radius(radius)
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

bool Sphere::hit(const Ray& ray) const
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
        return false;
    }

    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);

    if(t1 >= 0 || t2 >= 0)
    {
        return true;
    }
    return false;
}

} // namespace raytracer
