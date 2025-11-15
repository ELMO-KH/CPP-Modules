#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>
#include <iomanip>

class contact
{
private:
	std::string fname;
	std::string lname;
	std::string nname;
	std::string phone_nb;
	std::string secret;

public:
	void fullParamiter();
	std::string get_fname() const;
	std::string get_lname() const;
	std::string get_nname() const;
	bool is_empty() const;
};

class phone_book
{
private:
	contact c[8];
	int index;
	int total;

public:
	phone_book();
	void create_contact(int *i);
	void search_contact();
};
#endif
