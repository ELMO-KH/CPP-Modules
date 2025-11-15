#include "contact.hpp"

void contact::fullParamiter()
{
	std::cout << "first name : ";
	std::getline(std::cin, fname);
	while (fname.empty())
	{
		std::cout << "first name cannot be empty : ";
		std::getline(std::cin, fname);
	}

	std::cout << "last name : ";
	std::getline(std::cin, lname);
	while (lname.empty())
	{
		std::cout << "last name cannot be empty : ";
		std::getline(std::cin, lname);
	}

	std::cout << "nickname : ";
	std::getline(std::cin, nname);
	while (nname.empty())
	{
		std::cout << "nickname cannot be empty : ";
		std::getline(std::cin, nname);
	}

	std::cout << "phone number : ";
	std::getline(std::cin, phone_nb);
	while (phone_nb.empty())
	{
		std::cout << "phone number cannot be empty : ";
		std::getline(std::cin, phone_nb);
	}

	std::cout << "darkest secret : ";
	std::getline(std::cin, secret);
	while (secret.empty())
	{
		std::cout << "darkest secret cannot be empty : ";
		std::getline(std::cin, secret);
	}
}

std::string contact::get_fname() const { return fname; }
std::string contact::get_lname() const { return lname; }
std::string contact::get_nname() const { return nname; }
bool contact::is_empty() const { return fname.empty(); }
void phone_book::create_contact(int *i)
{
	c[*i % 8].fullParamiter();
	if (total < 8)
		total++;
	(*i)++;
}

void phone_book::search_contact()
{
	if (total == 0)
	{
		std::cout << "phonebook is empty!" << std::endl;
		return;
	}

	std::cout << "|" << std::setw(10) << "index" << "|"
			  << std::setw(10) << "first name" << "|"
			  << std::setw(10) << "last name" << "|"
			  << std::setw(10) << "nickname" << "|" << std::endl;

	for (int j = 0; j < total; j++)
	{
		std::string fn = c[j].get_fname();
		std::string ln = c[j].get_lname();
		std::string nn = c[j].get_nname();

		if (fn.length() > 10)
			fn = fn.substr(0, 9) + ".";
		if (ln.length() > 10)
			ln = ln.substr(0, 9) + ".";
		if (nn.length() > 10)
			nn = nn.substr(0, 9) + ".";

		std::cout << "|" << std::setw(10) << j << "|"
				  << std::setw(10) << fn << "|"
				  << std::setw(10) << ln << "|"
				  << std::setw(10) << nn << "|" << std::endl;
	}

	std::cout << "enter index : ";
	int idx;
	std::cin >> idx;

	if (std::cin.fail() || idx < 0 || idx >= total)
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "invalid index!" << std::endl;
		return;
	}

	std::cin.ignore(1000, '\n');

	std::cout << "First name: " << c[idx].get_fname() << std::endl;
	std::cout << "Last name: " << c[idx].get_lname() << std::endl;
	std::cout << "Nickname: " << c[idx].get_nname() << std::endl;
}

phone_book::phone_book()
{
	index = 0;
	total = 0;
}
