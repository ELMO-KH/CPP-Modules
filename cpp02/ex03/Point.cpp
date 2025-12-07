#include "Point.hpp"

Point::Point() : x(0), y(0)
{
}

Point::Point(const float xVal, const float yVal) : x(xVal), y(yVal)
{
}

Point::Point(const Point &copy) : x(copy.x), y(copy.y)
{
}

Point &Point::operator=(const Point &copy)
{
    (void)copy;
    return *this;
}

Point::~Point()
{
}

Fixed Point::getX() const
{
    return this->x;
}

Fixed Point::getY() const
{
    return this->y;
}
