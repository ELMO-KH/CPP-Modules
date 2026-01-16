#include "Intern.hpp"
#include <iostream>

Intern::Intern() {}

Intern::Intern(const Intern &other)
{
	*this = other;
}

Intern &Intern::operator=(const Intern &other)
{
	(void)other;
	return *this;
}

Intern::~Intern() {}

static AForm *makeShrubbery(std::string target)
{
	return new ShrubberyCreationForm(target);
}

static AForm *makeRobotomy(std::string target)
{
	return new RobotomyRequestForm(target);
}

static AForm *makePresidential(std::string target)
{
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string name, std::string target)
{
	std::string formNames[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"};
	AForm *(*forms[])(std::string target) = {
		&makeShrubbery,
		&makeRobotomy,
		&makePresidential};

	for (int i = 0; i < 3; i++)
	{
		if (name == formNames[i])
		{
			std::cout << "Intern creates " << name << std::endl;
			return forms[i](target);
		}
	}
	std::cout << "Intern could not create form named '" << name << "'" << std::endl;
	return NULL;
}
