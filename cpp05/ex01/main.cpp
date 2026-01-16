#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
	std::cout << "--- Test 1: Creating Forms ---" << std::endl;
	try
	{
		Form contract("Contract A", 50, 100);
		std::cout << contract << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "\n--- Test 2: Invalid Form Creation ---" << std::endl;
	try
	{
		Form bad("Bad Form", 0, 100);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "\n--- Test 3: Signing Form (Success) ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 40);
		Form contract("Contract B", 50, 100);

		std::cout << bob << std::endl;
		std::cout << contract << std::endl;

		bob.signForm(contract);
		std::cout << contract << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "\n--- Test 4: Signing Form (Failure) ---" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 60);
		Form contract("Contract C", 50, 100);

		std::cout << alice << std::endl;
		std::cout << contract << std::endl;

		alice.signForm(contract);
		std::cout << contract << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}
