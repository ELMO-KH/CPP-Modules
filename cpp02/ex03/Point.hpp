#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point{
    private:
        const Fixed x;
        const Fixed y;

    public:
    Point();
    Point(const float xVal, const float yVal);
    Point(const Point &copy);
    Point &operator=(const Point &copy);
    ~Point();
    
    Fixed getX() const;
    Fixed getY() const;
};

bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif
