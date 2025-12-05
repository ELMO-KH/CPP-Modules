#include "Zombie.hpp"

int main ()
{
    int N = 5;

    Zombie *horde;

    horde = zombieHorde(N, "zombie");
    for (int i = 0; i < N; i++)
    {
        horde[i].announce();
    }
    delete[] horde;
}
