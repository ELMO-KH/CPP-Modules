#include "Harl.hpp"

int main (int ac, char *av[]) {
    if (ac != 2) {
        std::cout << "Usage: ./harlFilter <level>" << std::endl;
        return 1;
    }
    Harl harl;
    void (Harl::*ptr)(std::string) = &Harl::complain;
    std::string level = av[1];
    (harl.*ptr)(level);
}