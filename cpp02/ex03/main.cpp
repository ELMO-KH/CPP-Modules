#include "Point.hpp"
#include <iostream>

int main( void ) {
    Point a(0.0f, 0.0f);
    Point b(10.0f, 0.0f);
    Point c(5.0f, 10.0f);
    
    Point point(5.0f, 0.0f);
    
	if (bsp(a, b, c, point))
    	std::cout << "Point inside: True "<< std::endl;
	else 
    	std::cout << "Point inside: False "<< std::endl;
    
    return 0;
}
