#include "math/vector.hpp"

#include <cmath>

Vector::Vector()
    : _x(0.0), _y(0.0), _z(0.0)
{
}

Vector::Vector(double x, double y, double z)
    : _x(x), _y(y), _z(z)
{
}

double Vector::x() const
{
    return _x;
}

double Vector::y() const
{
    return _y;
}

double Vector::z() const
{
    return _z;
}

Vector Vector::operator+(const Vector& other) const
{
    return Vector(_x + other._x, _y + other._y, _z + other._z);
}

Vector Vector::operator-(const Vector& other) const
{
    return Vector(_x - other._x, _y - other._y, _z - other._z);
}

Vector Vector::operator*(double scalar) const
{
    return Vector(_x * scalar, _y * scalar, _z * scalar);
}

double Vector::dot(const Vector& other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

Vector Vector::normalised() const
{
    const double length = std::sqrt(dot(*this));
    return Vector(_x / length, _y / length, _z / length);
}

Vector operator*(double scalar, const Vector& v)
{
    return v * scalar;
}
