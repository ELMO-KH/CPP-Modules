#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "--- Subject Main ---" << std::endl;
	const Animal* dog = new Dog();
	const Animal* cat = new Cat();
	delete dog;
	delete cat;

	std::cout << std::endl << "--- Array of Animals ---" << std::endl;
	int N = 4;
	Animal* animals[N];

	for (int k = 0; k < N / 2; k++)
		animals[k] = new Dog();
	for (int k = N / 2; k < N; k++)
		animals[k] = new Cat();

	std::cout << "Deleting animals..." << std::endl;
	for (int k = 0; k < N; k++)
		delete animals[k];

	std::cout << std::endl << "--- Deep Copy Test ---" << std::endl;
	Dog basic;
	{
		Dog tmp(basic);
	}
	std::cout << "End of Deep Copy Test" << std::endl;

	return 0;
}
