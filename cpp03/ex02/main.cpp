#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main() {
	std::cout << "=== Testing FragTrap Construction Chain ===" << std::endl;
	FragTrap frag1("naruto");

	std::cout << "\n=== Testing FragTrap attacks ===" << std::endl;
	frag1.attack("madara");
	frag1.attack("saski");

	std::cout << "\n=== Testing damage and repair ===" << std::endl;
	frag1.takeDamage(40);
	frag1.beRepaired(30);

	std::cout << "\n=== Testing special ability ===" << std::endl;
	frag1.highFivesGuys();

	std::cout << "\n=== Testing with ScavTrap ===" << std::endl;
	ScavTrap scav1("akachi");
	scav1.attack("gara");
	scav1.guardGate();

	std::cout << "\n=== Testing Destruction Chain ===" << std::endl;
	{
		FragTrap frag2("hunter");
		frag2.highFivesGuys();
	}

	std::cout << "\n=== Main Destruction ===" << std::endl;
	return 0;
}
