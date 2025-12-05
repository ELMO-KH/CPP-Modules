#include "Zombie.hpp"

int main (void)
{

    Zombie *zombie;
    zombie = newZombie("mostafa");
    zombie->announce();
    randomChump("ahmed");
    delete zombie;
    return 0;
}
