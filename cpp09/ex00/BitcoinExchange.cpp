#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {
	loadDatabase();
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange &other ) {
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange &other ) {
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string	BitcoinExchange::trim( const std::string &str ) {
	size_t	start = str.find_first_not_of(" \t\r\n");
	size_t	end = str.find_last_not_of(" \t\r\n");

	if (start == std::string::npos)
		return "";
	return str.substr(start, end - start + 1);
}

bool	BitcoinExchange::isLeapYear( int year ) {
	if (year % 400 == 0)
		return true;
	if (year % 100 == 0)
		return false;
	return year % 4 == 0;
}

bool	BitcoinExchange::isValidDate( const std::string &date ) {
	int	year;
	int	month;
	int	day;
	int	days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.length(); i++) {
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}
	std::istringstream(date.substr(0, 4)) >> year;
	std::istringstream(date.substr(5, 2)) >> month;
	std::istringstream(date.substr(8, 2)) >> day;
	if (month < 1 || month > 12)
		return false;
	if (isLeapYear(year))
		days_in_month[1] = 29;
	return day >= 1 && day <= days_in_month[month - 1];
}

double	BitcoinExchange::parseValue( const std::string &token ) {
	char	*end;
	double	value;

	if (token.empty())
		throw std::invalid_argument("Error: bad input");
	value = std::strtod(token.c_str(), &end);
	if (end == token.c_str() || *end != '\0' || errno == ERANGE)
		throw std::invalid_argument("Error: bad input");
	if (value < 0)
		throw std::invalid_argument("Error: not a positive number.");
	if (value > 1000)
		throw std::invalid_argument("Error: too large a number.");
	return value;
}

void	BitcoinExchange::processDataLine( const std::string &line ) {
	std::istringstream	stream(line);
	std::string			date;
	std::string			rate_text;
	char				*end;
	double				rate;

	if (!std::getline(stream, date, ',') || !std::getline(stream, rate_text))
		throw std::runtime_error("Error: invalid database.");
	date = trim(date);
	rate_text = trim(rate_text);
	if (!isValidDate(date))
		throw std::runtime_error("Error: invalid database.");
	rate = std::strtod(rate_text.c_str(), &end);
	if (end == rate_text.c_str() || *end != '\0' || errno == ERANGE)
		throw std::runtime_error("Error: invalid database.");
	_data[date] = rate;
}

void	BitcoinExchange::loadDatabase( void ) {
	std::ifstream	data("data.csv");
	std::string		line;

	if (!data.is_open())
		throw std::runtime_error("Error: could not open database.");
	if (!std::getline(data, line) || trim(line) != "date,exchange_rate")
		throw std::runtime_error("Error: invalid database.");
	while (std::getline(data, line)) {
		if (!trim(line).empty())
			processDataLine(line);
	}
	if (_data.empty())
		throw std::runtime_error("Error: invalid database.");
}

double	BitcoinExchange::getExchangeRate( const std::string &date ) const {
	std::map<std::string, double>::const_iterator	it = _data.lower_bound(date);

	if (it != _data.end() && it->first == date)
		return it->second;
	if (it == _data.begin())
		throw std::invalid_argument("Error: bad input => " + date);
	--it;
	return it->second;
}

void	BitcoinExchange::processInputLine( const std::string &line ) {
	size_t		separator = line.find('|');
	std::string	date;
	std::string	value_text;
	double		value;
	double		rate;

	if (separator == std::string::npos || line.find('|', separator + 1) != std::string::npos) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return ;
	}
	date = trim(line.substr(0, separator));
	value_text = trim(line.substr(separator + 1));
	if (!isValidDate(date)) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return ;
	}
	try {
		value = parseValue(value_text);
		rate = getExchangeRate(date);
		std::cout << date << " => " << value << " = " << value * rate << std::endl;
	} catch (const std::invalid_argument &e) {
		if (std::string(e.what()) == "Error: bad input")
			std::cerr << "Error: bad input => " << line << std::endl;
		else
			std::cerr << e.what() << std::endl;
	}
}

void	BitcoinExchange::processInputFile( const std::string &file ) {
	std::ifstream	input(file.c_str());
	std::string		line;

	if (!input.is_open())
		throw std::runtime_error("Error: could not open file.");
	if (!std::getline(input, line) || trim(line) != "date | value")
		throw std::runtime_error("Error: invalid input file.");
	while (std::getline(input, line)) {
		if (!trim(line).empty())
			processInputLine(line);
	}
}
