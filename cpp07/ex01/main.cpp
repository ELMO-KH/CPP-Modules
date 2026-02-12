#include <iostream>
#include "iter.hpp"

class test
{
	private:
		int _n;

	public:
		test(void) : _n(42) {}
		int get(void) const { return this->_n; }

};

std::ostream &operator<<(std::ostream &o, test const &rhs)
{
	o << rhs.get();
	return o;
}

template <typename T>
void print(T const &x)
{
	std::cout << x << std::endl;
}

void increment(int &n)
{
	n++;
}

int main(void)
{
	int tab[] = {0, 1, 2, 3, 4};
	test tab2[5];

	std::cout << "--- Int array ---" << std::endl;
	iter(tab, 5, print<int>);

	std::cout << "--- test array ---" << std::endl;
	iter(tab2, 5, print<test>);

	std::cout << "--- Modify int array ---" << std::endl;
	iter(tab, 5, increment);
	iter(tab, 5, print<int>);

	std::cout << "--- Const array ---" << std::endl;
	const int constTab[] = {10, 20, 30};
	iter(constTab, 3, print<int>);

	return 0;
}
