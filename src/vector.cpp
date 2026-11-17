#include "raytracer/vector.hpp"

namespace raytracer {

Vector::Vector()
    : x_(0.0), y_(0.0), z_(0.0)
{
}

Vector::Vector(double x, double y, double z)
    : x_(x), y_(y), z_(z)
{
}

double Vector::getX() const
{
    return x_;
}

double Vector::getY() const
{
    return y_;
}

double Vector::getZ() const
{
    return z_;
}

Vector Vector::add(const Vector& other) const
{
    return Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector Vector::subtract(const Vector& other) const
{
    return Vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

} // namespace raytracer
