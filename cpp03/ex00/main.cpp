#include "ClapTrap.hpp"

int main() {
	std::cout << "=== Creating ClapTraps ===" << std::endl;
	ClapTrap clap1("naruto");
	ClapTrap clap2("saski");

	std::cout << "\n=== Testing attacks ===" << std::endl;
	clap1.attack("madara");
	clap1.attack("itachi");

	std::cout << "\n=== Testing damage ===" << std::endl;
	clap2.takeDamage(3);
	clap2.takeDamage(5);

	std::cout << "\n=== Testing repair ===" << std::endl;
	clap2.beRepaired(4);

	std::cout << "\n=== Testing energy depletion ===" << std::endl;
	for (int i = 0; i < 10; i++) {
		clap1.attack("madara");
	}
	clap1.attack("madara");

	std::cout << "\n=== Testing destruction ===" << std::endl;
	clap2.takeDamage(20);
	clap2.attack("itachi");
	clap2.beRepaired(5);

	std::cout << "\n=== Destroying ClapTraps ===" << std::endl;
	return 0;
}
