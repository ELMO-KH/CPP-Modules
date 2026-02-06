#include "Base.hpp"
#include <iostream>

int main()
{
	Base *ptr = generate();

	std::cout << "\nIdentify by pointer: ";
	identify(ptr);

	std::cout << "Identify by reference: ";
	identify(*ptr);

	delete ptr;

	std::cout << "\n--- Multiple tests ---" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		Base *test = generate();
		std::cout << "Pointer: ";
		identify(test);
		std::cout << "Reference: ";
		identify(*test);
		delete test;
		std::cout << std::endl;
	}

	return 0;
}
