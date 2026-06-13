#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _data;
public:
    BitcoinExchange();
    void processInputFile(std::string file);
    void processLine(const std::string& line);
    ~BitcoinExchange();
};

#endif
