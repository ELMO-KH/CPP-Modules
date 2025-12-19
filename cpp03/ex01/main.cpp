#include "ScavTrap.hpp"

int main() {
	ScavTrap scav1("buruto");

	scav1.attack("gara");
	scav1.attack("saski");

	std::cout << "\n=== Testing damage and repair ===" << std::endl;
	scav1.takeDamage(30);
	scav1.beRepaired(20);
	scav1.takeDamage(50);

	std::cout << "\n=== Testing special ability ===" << std::endl;
	scav1.guardGate();

	std::cout << "\n=== Testing with ClapTrap ===" << std::endl;
	ClapTrap clap1("madara");
	clap1.attack("buroto");

	std::cout << "\n=== Testing Destruction Chain ===" << std::endl;
	{
		ScavTrap scav2("itatchi");
		scav2.guardGate();
	}

	return 0;
}
