#include "Harl.hpp"

void Harl::debug( void ) {
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}

void Harl::info( void ) {
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning( void ) {
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error( void ) {
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain( std::string level) {
    std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    int i = 0;
    while (i < 4 && levels[i] != level)
        i++;

    switch (i)
    {
    case 0:
        debug();
        // Fallthrough
    case 1:
        info();
        // Fallthrough
    case 2:
        warning();
        // Fallthrough
    case 3:
        error();
        break;
    default:
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }
}
