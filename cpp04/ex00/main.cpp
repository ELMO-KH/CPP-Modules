#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;

	std::cout << "------------------------------------------------" << std::endl;

	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongI = new WrongCat();

	std::cout << wrongI->getType() << " " << std::endl;
	wrongI->makeSound();
	wrongMeta->makeSound();

	delete wrongMeta;
	delete wrongI;

	std::cout << "------------------------------------------------" << std::endl;

	Dog dog1;
	Dog dog2(dog1);
	Dog dog3;
	dog3 = dog1;

	std::cout << "dog1 type: " << dog1.getType() << std::endl;
	std::cout << "dog2 type: " << dog2.getType() << std::endl;
	std::cout << "dog3 type: " << dog3.getType() << std::endl;

	dog1.makeSound();
	dog2.makeSound();
	dog3.makeSound();

	return 0;
}
