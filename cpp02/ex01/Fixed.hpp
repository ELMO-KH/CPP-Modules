#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>
class Fixed
{
private:
	int 				_fixedPointValue;
	static const int 	_fractionalBits = 8;

public:
	Fixed();							  // Default constructor
	Fixed(const Fixed &copy);			  // Copy constructor
	Fixed &operator=(const Fixed &copy); // Copy assignment operator
	Fixed(const int value);
	Fixed(const float value);
	~Fixed();							  // Destructor

	int getRawBits(void) const;
	void setRawBits(int const raw);
	float toFloat(void) const;
	int toInt(void) const;
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);
#endif
