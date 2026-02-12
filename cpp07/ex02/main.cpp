#include <iostream>
#include "Array.hpp"
#include <cstdlib>
#include <ctime>

#define MAX_VAL 750

int main(int, char **)
{
	Array<int> numbers(MAX_VAL);
	int *mirror = new int[MAX_VAL];
	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}
	try
	{
		numbers[-2] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}
	delete[] mirror;

	std::cout << "\n=== Additional Tests ===" << std::endl;

	Array<int> empty;
	std::cout << "Empty array size: " << empty.size() << std::endl;

	Array<std::string> strings(5);
	strings[0] = "Hello";
	strings[1] = "World";
	std::cout << "String array[0]: " << strings[0] << std::endl;
	std::cout << "String array[1]: " << strings[1] << std::endl;

	Array<float> floats(3);
	floats[0] = 3.14f;
	floats[1] = 2.71f;
	floats[2] = 1.41f;
	std::cout << "Float array[0]: " << floats[0] << std::endl;
	std::cout << "Float array size: " << floats.size() << std::endl;

	std::cout << "\n=== All tests passed! ===" << std::endl;
	return 0;
}
