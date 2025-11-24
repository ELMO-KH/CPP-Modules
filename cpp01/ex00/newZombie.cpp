#include "Zombie.hpp"

void Zombie::set_name( std::string zname)
{
    name = zname;
}

Zombie* newZombie( std::string name )
{
    Zombie *z = new Zombie();
    z->set_name(name);
    return z;
}