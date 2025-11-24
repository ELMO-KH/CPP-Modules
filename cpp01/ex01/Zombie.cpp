#include "Zombie.hpp"

Zombie::Zombie()
{
}

void Zombie::set_name(std::string zname)
{
    name = zname;
}

void Zombie::announce( void )
{
    std::cout << name << index << ": BraiiiiiiinnnzzzZ..." << std::endl;
}