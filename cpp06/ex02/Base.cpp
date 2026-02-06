#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base::~Base() {}

Base *generate(void)
{
	static bool seeded = false;
	if (!seeded)
	{
		std::srand(std::time(NULL));
		seeded = true;
	}

	int random = std::rand() % 3;

	if (random == 0)
	{
		std::cout << "Generated: A" << std::endl;
		return new A();
	}
	else if (random == 1)
	{
		std::cout << "Generated: B" << std::endl;
		return new B();
	}
	else
	{
		std::cout << "Generated: C" << std::endl;
		return new C();
	}
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (std::exception &)
	{
	}

	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (std::exception &)
	{
	}

	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (std::exception &)
	{
	}

	std::cout << "Unknown type" << std::endl;
}
