#include "Sed.hpp"

int main(int ac, char *av[])
{
    if (ac != 4) {
        std::cerr << "Usage: ./sed_is_for_losers <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    Sed sed(av[1]);
    sed.replace(av[2], av[3]);

    return 0;
}
