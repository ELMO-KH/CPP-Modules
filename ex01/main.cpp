#include "contact.hpp"

int main(int ac, char **av)
{
	(void)**av;
	if (ac != 1)
	{
		std::cout << "error, no need argument" << std::endl;
		return 0;
	}

	phone_book PB;
	std::string buffer;
	int i = 0;
	while (true)
	{
		std::cout << "enter command : ";
		std::getline(std::cin, buffer);

		if (std::cin.eof())
			break;

		if (buffer == "ADD")
		{
			PB.create_contact(&i);
		}
		else if (buffer == "SEARCH")
		{
			PB.search_contact();
		}
		else if (buffer == "EXIT")
		{
			std::cout << "exit " << std::endl;
			break;
		}
		else if (!buffer.empty())
			std::cout << "chose ADD or SEARCH or EXIT" << std::endl;
	}
	return 0;
}
