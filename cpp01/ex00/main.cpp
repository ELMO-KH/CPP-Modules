#include "Zombie.hpp"

int main (void)
{

    Zombie *zombie;
    zombie = newZombie("mostafa");
    zombie->announce();
    randomChump("hhhh");
    delete zombie;
    return 0;
}