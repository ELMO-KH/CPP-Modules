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

typedef std::vector<int>::iterator _it;

class PmergeMe {

public:

	PmergeMe( void );
	PmergeMe( const  PmergeMe &Other );
	PmergeMe &operator=( const PmergeMe &Other );
	~PmergeMe( void );
	void	hanleArgument( char **const arv );
	bool	IsDigit( std::string &str);
	void	PrintBefor( void );
	void	PrintAfter( void );
	void	sort( void );

	template <typename T>
	void	PrintStatusContainer( T &Container, clock_t duration );
	template <typename T>
	void	PairingPhase( T& container, int pair_level );
	template <typename T>
	void	InsertionPhase(T &container, int pair_level );

private:

	std::vector<int> 					_vectorData;
	std::deque<int>						_dequeData;

	typedef std::deque<int>::iterator	_itdeque;
	typedef std::vector<int>::iterator	_itvector;
};

extern int	check;

size_t	GeneratJacobsthalNumber(size_t k);

template <typename T>
T		next(T  it, int steps) {
	std::advance(it, steps);
	return it;
}

template <typename T>
bool	_comp(T a, T b) {
	check++;
	return *a < *b;
}

template	<typename T>
void	_swap_pair(T it, int pair_level) {

	T	start = next(it, 1 - pair_level);
	T	end = next(start, pair_level);
	while (start != end) {
		std::iter_swap(start, next(start, pair_level));
		start++;
	}
}

template <typename T>
void	PmergeMe::PrintStatusContainer( T &Container, clock_t duration ) {

	std::cout.precision(6);
	double seconds = (double)duration / CLOCKS_PER_SEC;
	double microseconds = seconds * 1000000;
	std::cout << "Time to process a range of " << Container.size() <<" elements with std::[..] : " << std::fixed << microseconds << " us" << std::endl;
}

template	<typename T>
void	PmergeMe::InsertionPhase(T &container, int pair_level)
{

	typedef typename T::iterator iter;
	typedef typename std::vector<iter>::iterator iter_chain;
	int pair_units_nbr = container.size() / pair_level;
	if (pair_units_nbr < 2) return;

	bool is_odd = (pair_units_nbr % 2 == 1);
	std::vector<iter> main_chain;
	std::vector<iter> pend_chain;

	main_chain.push_back(container.begin() + pair_level - 1);
	main_chain.push_back(container.begin() + pair_level * 2 - 1);

	for (int i = 4; i <= pair_units_nbr; i += 2) {
		pend_chain.push_back(container.begin() + pair_level * (i - 1) - 1);
		main_chain.push_back(container.begin() + pair_level * i - 1);
	}
	if (is_odd) {
		pend_chain.push_back(container.begin() + (pair_level * pair_units_nbr) - 1);
	}

	int prev_jac = 1;
	int inserted = 0;

	for (int k = 2; true ; k++) {
		int curr_jac = GeneratJacobsthalNumber(k);
		int jac_diff = curr_jac - prev_jac; 
		
		if (jac_diff > (int)pend_chain.size()) break; 
		
		for (int i = jac_diff - 1; i >= 0 && !pend_chain.empty(); i--) { 
			iter_chain pend_it = pend_chain.begin() + i;
			iter_chain bound_it = main_chain.begin() + std::min((int)main_chain.size(), curr_jac + inserted);
			iter_chain pos = std::upper_bound(main_chain.begin(), bound_it, *pend_it, _comp<iter>);
			main_chain.insert(pos, *pend_it);
			pend_chain.erase(pend_it);
		}
		prev_jac = curr_jac; 
		inserted += jac_diff;
	}

	while (!pend_chain.empty()) {
		iter_chain pend_it = pend_chain.end() - 1;
		iter_chain pos = std::upper_bound(main_chain.begin(), main_chain.end(), *pend_it, _comp<iter>);

		main_chain.insert(pos, *pend_it);
		pend_chain.pop_back();
	}

	std::vector<int> result;
	result.reserve(container.size());
    for (iter_chain it = main_chain.begin(); it != main_chain.end(); it++) {
		iter base = *it;
		for (int i = 0; i < pair_level; i++) {
			iter pair_start = base - pair_level + 1 + i;
			result.push_back(*pair_start);
		}
	}

	for (size_t i = 0; i < result.size(); i++)
		container[i] = result[i];	
}

template <typename T>
void	PmergeMe::PairingPhase( T& container, int pair_level) {

	typedef typename T::iterator Iterator;
	int pair_units_nbr = container.size() / pair_level;
	if (pair_units_nbr < 2)
		return;

	bool is_odd = ((pair_units_nbr % 2) == 1);
	Iterator start = container.begin();
	Iterator last = next(container.begin(), pair_level * (pair_units_nbr));
	Iterator end = next(last, -(is_odd * pair_level));

	int jump = 2 * pair_level;
	for (Iterator it = start; it != end; std::advance(it, jump))
	{
		Iterator this_pair = next(it, pair_level - 1);
		Iterator next_pair = next(it, pair_level * 2 - 1);
		if (_comp(next_pair, this_pair)) 
			_swap_pair(this_pair, pair_level);
	}


	PairingPhase(container, pair_level * 2);

	InsertionPhase(container, pair_level);
}