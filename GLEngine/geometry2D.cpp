#include <iostream>
#include <array>
#include <GLFW/glfw3.h>
#include "geometry2D.hpp"

Vector::Vector ()
    : x(0.f), y(0.f), z(0.f) {}

Vector::Vector (float x, float y, float z)
    : x(x), y(y), z(z) {}

void Point::operator=(const Point & rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

Vector Vector::operator+(const Vector & rhs)
{
    Vector vector;
    vector.x = x + rhs.x;
    vector.y = y + rhs.y;
    vector.z = z + rhs.z;

    return vector;
}

Vector Vector::operator-(const Vector & rhs)
{
    Vector vector;
    vector.x = x - rhs.x;
    vector.y = y - rhs.y;
    vector.z = z - rhs.z;

    return vector;
}

Point::Point ()
    : x(0.f), y(0.f), z(0.f), r(1.f), g(0.f), b(0.f) {}

Point::Point (float x, float y, float z)
    : x(x), y(y), z(z), r(1.f), g(1.f), b(1.f) {}

Point::Point (float x, float y, float z, float r, float g, float b)
    : x(x), y(y), z(z), r(r), g(g), b(b) {}

Point Point::operator+(const Point & rhs)
{
    Point point;
    point.x = x + rhs.x;
    point.y = y + rhs.y;
    point.z = z + rhs.z;

    return point;
}

Vector Point::operator-(const Point & rhs)
{
    Vector vector;
    vector.x = x - rhs.x;
    vector.y = y - rhs.y;
    vector.z = z - rhs.z;

    return vector;
}

Point Point::operator+(const Vector & rhs)
{
    Point point;
    point.x = x + rhs.x;
    point.y = y + rhs.y;
    point.z = z + rhs.z;

    return point;
}

Point Point::operator-(const Vector & rhs)
{
    Point point;
    point.x = x - rhs.x;
    point.y = y - rhs.y;
    point.z = z - rhs.z;

    return point;
}

const float Point::getX() const
{
    return x;
}

const float Point::getY() const
{
    return y;
}

const float Point::getZ() const
{
    return z;
}

const float Point::getR() const
{
    return r;
}

const float Point::getG() const
{
    return g;
}

const float Point::getB() const
{
    return b;
}