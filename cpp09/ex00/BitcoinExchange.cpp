#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::processLine(const std::string& line) {
    
    std::istringstream iss(line);
    std::string date;
    std::string exchange;

    std::getline(iss, date, ',');
    std::getline(iss, exchange);

    double value;
    std::istringstream iss_exchange(exchange);
    iss_exchange >> value;
    _data.insert(std::make_pair(date, value));
}

void BitcoinExchange::processInputFile(std::string file){
    std::ifstream input(file.c_str());

    if (!input.is_open())
    {
        std::cerr << "open file failed" << std::endl;
        return ;
    }
    std::string line;
    while (std::getline(input, line))
    {
        processLine(line);
    }
    input.close();
}
