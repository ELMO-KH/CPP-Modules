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

		void	loadDatabase( void );
		void	processDataLine( const std::string &line );
		void	processInputLine( const std::string &line );
		double	getExchangeRate( const std::string &date ) const;

		static bool			isValidDate( const std::string &date );
		static bool			isLeapYear( int year );
		static std::string	trim( const std::string &str );
		static double		parseValue( const std::string &token );

	public:
		BitcoinExchange();
		BitcoinExchange( const BitcoinExchange &other );
		BitcoinExchange &operator=( const BitcoinExchange &other );
		~BitcoinExchange();

		void	processInputFile( const std::string &file );
};

#endif
