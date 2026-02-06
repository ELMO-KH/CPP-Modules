#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data originalData;
	originalData.value = 42;
	originalData.name = "Test Data";

	std::cout << "Original Data:" << std::endl;
	std::cout << "  Address: " << &originalData << std::endl;
	std::cout << "  Value: " << originalData.value << std::endl;
	std::cout << "  Name: " << originalData.name << std::endl;
	std::cout << std::endl;

	uintptr_t serialized = Serializer::serialize(&originalData);
	std::cout << "Serialized (uintptr_t): " << serialized << std::endl;
	std::cout << std::endl;

	Data *deserialized = Serializer::deserialize(serialized);
	std::cout << "Deserialized Data:" << std::endl;
	std::cout << "  Address: " << deserialized << std::endl;
	std::cout << "  Value: " << deserialized->value << std::endl;
	std::cout << "  Name: " << deserialized->name << std::endl;
	std::cout << std::endl;

	if (deserialized == &originalData)
	{
		std::cout << "✓ Success: Pointers match!" << std::endl;
	}
	else
	{
		std::cout << "✗ Error: Pointers don't match!" << std::endl;
	}

	return 0;
}
