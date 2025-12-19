#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << this->name << " has been constructed!" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
	std::cout << "FragTrap copy constructor called" << std::endl;
	*this = other;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
	std::cout << "FragTrap assignment operator called" << std::endl;
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap " << this->name << " has been destroyed!" << std::endl;
}

void FragTrap::attack(const std::string& target) {
	if (this->energyPoints == 0) {
		std::cout << "FragTrap " << this->name << " has no energy points left to attack!" << std::endl;
		return;
	}
	if (this->hitPoints == 0) {
		std::cout << "FragTrap " << this->name << " has no hit points left to attack!" << std::endl;
		return;
	}
	this->energyPoints--;
	std::cout << "FragTrap " << this->name << " attacks " << target
			  << ", causing " << this->attackDamage << " points of damage!" << std::endl;
}

void FragTrap::takeDamage(unsigned int amount) {
	if (this->hitPoints == 0) {
		std::cout << "FragTrap " << this->name << " is already destroyed!" << std::endl;
		return;
	}
	if (amount >= this->hitPoints) {
		this->hitPoints = 0;
		std::cout << "FragTrap " << this->name << " takes " << amount
				  << " points of damage and is destroyed!" << std::endl;
	} else {
		this->hitPoints -= amount;
		std::cout << "FragTrap " << this->name << " takes " << amount
				  << " points of damage! (" << this->hitPoints << " HP remaining)" << std::endl;
	}
}

void FragTrap::beRepaired(unsigned int amount) {
	if (this->energyPoints == 0) {
		std::cout << "FragTrap " << this->name << " has no energy points left to repair!" << std::endl;
		return;
	}
	if (this->hitPoints == 0) {
		std::cout << "FragTrap " << this->name << " has no hit points left to repair!" << std::endl;
		return;
	}
	this->energyPoints--;
	this->hitPoints += amount;
	std::cout << "FragTrap " << this->name << " repairs itself for " << amount
			  << " hit points! (" << this->hitPoints << " HP total)" << std::endl;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap " << this->name << " requests a positive high five! ✋" << std::endl;
}
