#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << "ClapTrap " << this->name << " has been constructed!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) {
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
	std::cout << "ClapTrap assignment operator called" << std::endl;
	if (this != &other) {
		this->name = other.name;
		this->hitPoints = other.hitPoints;
		this->energyPoints = other.energyPoints;
		this->attackDamage = other.attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap " << this->name << " has been destroyed!" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
	if (this->energyPoints == 0) {
		std::cout << "ClapTrap " << this->name << " has no energy points left to attack!" << std::endl;
		return;
	}
	if (this->hitPoints == 0) {
		std::cout << "ClapTrap " << this->name << " has no hit points left to attack!" << std::endl;
		return;
	}
	this->energyPoints--;
	std::cout << "ClapTrap " << this->name << " attacks " << target
			  << ", causing " << this->attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (this->hitPoints == 0) {
		std::cout << "ClapTrap " << this->name << " is already destroyed!" << std::endl;
		return;
	}
	if (amount >= this->hitPoints) {
		this->hitPoints = 0;
		std::cout << "ClapTrap " << this->name << " takes " << amount
				  << " points of damage and is destroyed!" << std::endl;
	} else {
		this->hitPoints -= amount;
		std::cout << "ClapTrap " << this->name << " takes " << amount
				  << " points of damage! (" << this->hitPoints << " HP remaining)" << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (this->energyPoints == 0) {
		std::cout << "ClapTrap " << this->name << " has no energy points left to repair!" << std::endl;
		return;
	}
	if (this->hitPoints == 0) {
		std::cout << "ClapTrap " << this->name << " has no hit points left to repair!" << std::endl;
		return;
	}
	this->energyPoints--;
	this->hitPoints += amount;
	std::cout << "ClapTrap " << this->name << " repairs itself for " << amount
			  << " hit points! (" << this->hitPoints << " HP total)" << std::endl;
}
