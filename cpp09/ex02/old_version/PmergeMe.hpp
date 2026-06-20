# pragma once
# include <iostream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <vector>
# include <deque>
# include <cctype>
# include <set>
# include <algorithm>
# include <ctime>

class PmergeMe {

public:

	PmergeMe( void );
	PmergeMe( const PmergeMe &other );
	PmergeMe &operator=( const PmergeMe &other );
	~PmergeMe( void );

	void	handleArguments( char **const argv );
	void	hanleArgument( char **const argv );
	void	sort( void );

private:

	std::vector<int>	_vectorData;
	std::deque<int>		_dequeData;

	bool	isPositiveNumber( const std::string &token ) const;
	void	printBefore( void ) const;
	void	printAfter( void ) const;

	template <typename T>
	void	printStatus( const T &container, clock_t duration ) const;
	template <typename T>
	void	pairingPhase( T& container, int pair_level );
	template <typename T>
	void	insertionPhase( T &container, int pair_level );
};

extern int	check;

size_t	generateJacobsthalNumber(size_t k);

template <typename Iterator>
Iterator	advanceIterator(Iterator it, int steps) {
	std::advance(it, steps);
	return it;
}

template <typename Iterator>
bool	comparePointedValues(Iterator lhs, Iterator rhs) {
	check++;
	return *lhs < *rhs;
}

template <typename Iterator>
void	swapPairUnits(Iterator it, int pair_level) {

	Iterator	start = advanceIterator(it, 1 - pair_level);
	Iterator	end = advanceIterator(start, pair_level);
	while (start != end) {
		std::iter_swap(start, advanceIterator(start, pair_level));
		start++;
	}
}

template <typename T>
void	PmergeMe::printStatus( const T &container, clock_t duration ) const {

	std::cout.precision(6);
	double seconds = (double)duration / CLOCKS_PER_SEC;
	double microseconds = seconds * 1000000;
	std::cout << "Time to process a range of " << container.size() << " elements with std::[..] : " << std::fixed << microseconds << " us" << std::endl;
}

template <typename T>
void	PmergeMe::insertionPhase( T &container, int pair_level )
{
	typedef typename T::iterator iter;
	typedef typename std::vector<iter>::iterator chain_iter;

	int	pair_units_nbr = container.size() / pair_level;
	if (pair_units_nbr < 2)
		return;

	bool				has_odd_unit = (pair_units_nbr % 2 == 1);
	std::vector<iter>	main_chain;
	std::vector<iter>	pend_chain;

	main_chain.push_back(container.begin() + pair_level - 1);
	main_chain.push_back(container.begin() + (pair_level * 2) - 1);

	for (int i = 4; i <= pair_units_nbr; i += 2) {
		pend_chain.push_back(container.begin() + pair_level * (i - 1) - 1);
		main_chain.push_back(container.begin() + pair_level * i - 1);
	}
	if (has_odd_unit)
		pend_chain.push_back(container.begin() + pair_level * pair_units_nbr - 1);

	int	previous_jacobsthal = 1;
	int	inserted = 0;

	for (int k = 2; true; k++) {
		int	current_jacobsthal = generateJacobsthalNumber(k);
		int	jacobsthal_diff = current_jacobsthal - previous_jacobsthal;

		if (jacobsthal_diff > (int)pend_chain.size())
			break;

		for (int i = jacobsthal_diff - 1; i >= 0 && !pend_chain.empty(); i--) {
			chain_iter	pend_it = pend_chain.begin() + i;
			chain_iter	bound_it = main_chain.begin() + std::min((int)main_chain.size(), current_jacobsthal + inserted);
			chain_iter	pos = std::upper_bound(main_chain.begin(), bound_it, *pend_it, comparePointedValues<iter>);

			main_chain.insert(pos, *pend_it);
			pend_chain.erase(pend_it);
		}
		previous_jacobsthal = current_jacobsthal;
		inserted += jacobsthal_diff;
	}

	while (!pend_chain.empty()) {
		chain_iter	pend_it = pend_chain.end() - 1;
		chain_iter	pos = std::upper_bound(main_chain.begin(), main_chain.end(), *pend_it, comparePointedValues<iter>);

		main_chain.insert(pos, *pend_it);
		pend_chain.pop_back();
	}

	std::vector<int> result;
	result.reserve(container.size());
	for (chain_iter it = main_chain.begin(); it != main_chain.end(); it++) {
		iter	base = *it;

		for (int i = 0; i < pair_level; i++) {
			iter	unit_it = base - pair_level + 1 + i;
			result.push_back(*unit_it);
		}
	}

		for (size_t i = 0; i < result.size(); i++)
			container[i] = result[i];
}

template <typename T>
void	PmergeMe::pairingPhase( T& container, int pair_level ) {

	typedef typename T::iterator iterator;

	int	pair_units_nbr = container.size() / pair_level;
	if (pair_units_nbr < 2)
		return;

	bool		has_odd_unit = ((pair_units_nbr % 2) == 1);
	iterator	start = container.begin();
	iterator	last = advanceIterator(container.begin(), pair_level * pair_units_nbr);
	iterator	end = advanceIterator(last, -(has_odd_unit * pair_level));

	int jump = 2 * pair_level;
	for (iterator it = start; it != end; std::advance(it, jump))
	{
		iterator	this_pair = advanceIterator(it, pair_level - 1);
		iterator	next_pair = advanceIterator(it, pair_level * 2 - 1);

		if (comparePointedValues(next_pair, this_pair))
			swapPairUnits(this_pair, pair_level);
	}


	pairingPhase(container, pair_level * 2);

	insertionPhase(container, pair_level);
}
