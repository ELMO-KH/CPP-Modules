#include "BitcoinExchange.hpp"

int main(int ac, char *av[])
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <input_file>" << std::endl;
        return 1;
    }

    BitcoinExchange bitcoinExchange;

    bitcoinExchange.processInputFile(av[1]);

    return 0;
}
