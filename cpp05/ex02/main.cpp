#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib>

int main()
{
	std::srand(time(NULL));

	std::cout << "--- Test 1: Shrubbery Creation ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 137);
		ShrubberyCreationForm shrub("Garden");

		std::cout << bob << std::endl;
		std::cout << shrub << std::endl;

		bob.signForm(shrub);
		bob.executeForm(shrub);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "\n--- Test 2: Robotomy Request ---" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 45);
		RobotomyRequestForm robot("Bender");

		std::cout << alice << std::endl;
		std::cout << robot << std::endl;

		alice.signForm(robot);
		alice.executeForm(robot);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "\n--- Test 3: Presidential Pardon ---" << std::endl;
	try
	{
		Bureaucrat zaphod("Zaphod", 5);
		PresidentialPardonForm pardon("Arthur Dent");

		std::cout << zaphod << std::endl;
		std::cout << pardon << std::endl;

		zaphod.signForm(pardon);
		zaphod.executeForm(pardon);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "\n--- Test 4: Execution Failure (Not Signed) ---" << std::endl;
	try
	{
		Bureaucrat dave("Dave", 1);
		ShrubberyCreationForm shrub("Forest");

		// Forgot to sign!
		dave.executeForm(shrub);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "\n--- Test 5: Execution Failure (Grade Too Low) ---" << std::endl;
	try
	{
		Bureaucrat eve("Eve", 140); // Too low for exec (137 needed)
		ShrubberyCreationForm shrub("Backyard");

		eve.signForm(shrub);	// Can sign (145 needed)
		eve.executeForm(shrub); // Cannot execute
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}
