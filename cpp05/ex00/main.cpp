#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
	std::cout << "--- Test 1: Valid initialization ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 1);
		std::cout << bob << std::endl;

		bob.incrementGrade();
		std::cout << "After increment: " << bob << std::endl;

		bob.decrementGrade();
		std::cout << "After decrement: " << bob << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 2: Grade too high initialization ---" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 0);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 3: Grade too low initialization ---" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 151);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 4: Increment exception ---" << std::endl;
	try
	{
		Bureaucrat dave("Dave", 1);
		std::cout << dave << std::endl;
		dave.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 5: Decrement exception ---" << std::endl;
	try
	{
		Bureaucrat eve("Eve", 150);
		std::cout << eve << std::endl;
		eve.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
