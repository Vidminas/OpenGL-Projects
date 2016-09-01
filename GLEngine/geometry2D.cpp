#include <iostream>
#include <cmath>
#include <vector>
#include <GLFW/glfw3.h>
#include "geometry2D.hpp"

Vector::Vector()
    : x (0.f), y (0.f), z (0.f) {}

Vector::Vector (float x, float y, float z)
    : x (x), y (y), z (z) {}

void Point::operator= (const Point& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

Vector Vector::operator+ (const Vector& rhs)
{
    Vector vector;
    vector.x = x + rhs.x;
    vector.y = y + rhs.y;
    vector.z = z + rhs.z;

    return vector;
}

Vector Vector::operator- (const Vector& rhs)
{
    Vector vector;
    vector.x = x - rhs.x;
    vector.y = y - rhs.y;
    vector.z = z - rhs.z;

    return vector;
}

Point::Point()
    : x (0.f), y (0.f), z (0.f), r (1.f), g (0.f), b (0.f) {}

Point::Point (float x, float y, float z)
    : x (x), y (y), z (z), r (1.f), g (1.f), b (1.f) {}

Point::Point (float x, float y, float z, float r, float g, float b)
    : x (x), y (y), z (z), r (r), g (g), b (b) {}

Point Point::operator+ (const Point& rhs)
{
    Point point;
    point.x = x + rhs.x;
    point.y = y + rhs.y;
    point.z = z + rhs.z;

    return point;
}

Vector Point::operator- (const Point& rhs)
{
    Vector vector;
    vector.x = x - rhs.x;
    vector.y = y - rhs.y;
    vector.z = z - rhs.z;

    return vector;
}

Point Point::operator+ (const Vector& rhs)
{
    Point point;
    point.x = x + rhs.x;
    point.y = y + rhs.y;
    point.z = z + rhs.z;

    return point;
}

Point Point::operator- (const Vector& rhs)
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

BresenhamLine::BresenhamLine (Point a, Point b)
    : mStart (a)
    , mEnd (b)
{

}

std::vector<Point> BresenhamLine::rasterise()
{
    std::vector<Point> pointsOnLine;
    float stepSize (0.5);

    float x (mStart.getX() );
    float y (mStart.getY() );
    float dx (mEnd.getX() - x);
    float dy (mEnd.getY() - y);
    float sx (copysign (stepSize, mEnd.getX() - x) );
    float sy (copysign (stepSize, mEnd.getY() - y) );

    float error (0);
    float gradient (std::abs (dy / dx) * stepSize);

    while ( (x != mEnd.getX() || y != mEnd.getY() ) && x <= 5.f)
    {
        pointsOnLine.push_back (Point (x, y, 0,
                                       1 - (mStart.getR() + (mEnd.getX() - x + mEnd.getY() - y) * (mEnd.getR() - mStart.getR() ) / (dx + dy) ),
                                       1 - (mStart.getG() + (mEnd.getX() - x + mEnd.getY() - y) * (mEnd.getG() - mStart.getG() ) / (dx + dy) ),
                                       1 - (mStart.getB() + (mEnd.getX() - x + mEnd.getY() - y) * (mEnd.getB() - mStart.getB() ) / (dx + dy) ) ) );

        std::cout << "Added point at X = " << x << " Y = " << y << " error is " << error << std::endl;
        x += sx;
        error += gradient;

        while (error * 2 >= stepSize)
        {
            y += sy;
            error -= stepSize;
        }
    }

    pointsOnLine.push_back (mEnd);

    return pointsOnLine;
}
