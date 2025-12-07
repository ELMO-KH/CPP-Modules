#include "Point.hpp"

static float absolute(float n)
{
    if (n < 0)
        return -n;
    return n;
}

static float calculateArea(const Point& p1, const Point& p2, const Point& p3)
{
    float x1 = p1.getX().toFloat();
    float y1 = p1.getY().toFloat();
    float x2 = p2.getX().toFloat();
    float y2 = p2.getY().toFloat();
    float x3 = p3.getX().toFloat();
    float y3 = p3.getY().toFloat();
    
    float area = absolute((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0f);

    return area;
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
    float areaABC = calculateArea(a, b, c);
    
    if (areaABC == 0)
        return false;
    
    float areaPAB = calculateArea(point, a, b);
    float areaPBC = calculateArea(point, b, c);
    float areaPCA = calculateArea(point, c, a);
    
    float epsilon = 1.0f / 256.0f;
    if (areaPAB < epsilon || areaPBC < epsilon || areaPCA < epsilon)
        return false;
    
    float sumAreas = areaPAB + areaPBC + areaPCA;
    
    if (absolute(sumAreas - areaABC) < epsilon)
        return true;
    
    return false;
}
