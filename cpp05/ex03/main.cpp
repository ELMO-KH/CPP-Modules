#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include <iostream>

int main()
{
	Intern someRandomIntern;
	AForm *rrf;

	std::cout << "--- Test 1: Robotomy Request ---" << std::endl;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	if (rrf)
	{
		Bureaucrat boss("Boss", 1);
		boss.signForm(*rrf);
		boss.executeForm(*rrf);
		delete rrf;
	}

	std::cout << "\n--- Test 2: Shrubbery Creation ---" << std::endl;
	AForm *scf = someRandomIntern.makeForm("shrubbery creation", "Garden");
	if (scf)
	{
		Bureaucrat boss("Boss", 1);
		boss.signForm(*scf);
		boss.executeForm(*scf);
		delete scf;
	}

	std::cout << "\n--- Test 3: Presidential Pardon ---" << std::endl;
	AForm *ppf = someRandomIntern.makeForm("presidential pardon", "Criminal");
	if (ppf)
	{
		Bureaucrat boss("Boss", 1);
		boss.signForm(*ppf);
		boss.executeForm(*ppf);
		delete ppf;
	}

	std::cout << "\n--- Test 4: Unknown Form ---" << std::endl;
	AForm *wrong;
	wrong = someRandomIntern.makeForm("not a form", "Target");
	if (wrong)
	{
		delete wrong;
	}

	return 0;
}
