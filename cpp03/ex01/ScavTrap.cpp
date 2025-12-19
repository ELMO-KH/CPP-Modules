#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	std::cout << "ScavTrap " << this->name << " has been constructed!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
	std::cout << "ScavTrap copy constructor called" << std::endl;
	*this = other;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
	std::cout << "ScavTrap assignment operator called" << std::endl;
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap " << this->name << " has been destroyed!" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
	if (this->energyPoints == 0) {
		std::cout << "ScavTrap " << this->name << " has no energy points left to attack!" << std::endl;
		return;
	}
	if (this->hitPoints == 0) {
		std::cout << "ScavTrap " << this->name << " has no hit points left to attack!" << std::endl;
		return;
	}
	this->energyPoints--;
	std::cout << "ScavTrap " << this->name << " fiercely attacks " << target
			  << ", causing " << this->attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::takeDamage(unsigned int amount) {
	if (this->hitPoints == 0) {
		std::cout << "ScavTrap " << this->name << " is already destroyed!" << std::endl;
		return;
	}
	if (amount >= this->hitPoints) {
		this->hitPoints = 0;
		std::cout << "ScavTrap " << this->name << " takes " << amount
				  << " points of damage and is destroyed!" << std::endl;
	} else {
		this->hitPoints -= amount;
		std::cout << "ScavTrap " << this->name << " takes " << amount
				  << " points of damage! (" << this->hitPoints << " HP remaining)" << std::endl;
	}
}

void ScavTrap::beRepaired(unsigned int amount) {
	if (this->energyPoints == 0) {
		std::cout << "ScavTrap " << this->name << " has no energy points left to repair!" << std::endl;
		return;
	}
	if (this->hitPoints == 0) {
		std::cout << "ScavTrap " << this->name << " has no hit points left to repair!" << std::endl;
		return;
	}
	this->energyPoints--;
	this->hitPoints += amount;
	std::cout << "ScavTrap " << this->name << " repairs itself for " << amount
			  << " hit points! (" << this->hitPoints << " HP total)" << std::endl;
}

void ScavTrap::guardGate() {
	std::cout << "ScavTrap " << this->name << " is now in Gate keeper mode!" << std::endl;
}
