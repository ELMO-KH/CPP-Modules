#pragma once

#include <ctime>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class PmergeMe {
public:
	PmergeMe( void );
	PmergeMe( const PmergeMe &other );
	PmergeMe &operator=( const PmergeMe &other );
	~PmergeMe( void );

	void	run( int argc, char **argv );

private:
	struct Element {
		int		value;
		size_t	id;

		Element( void );
		Element( int value, size_t id );
	};

	struct Pair {
		Element	small;
		Element	large;

		Pair( const Element &first, const Element &second );
	};

	struct Pending {
		Element	value;
		size_t	bound_id;
		bool	has_bound;

		Pending( const Element &value, size_t bound_id );
		Pending( const Element &value );
	};

	std::vector<int>	_vector_data;
	std::deque<int>		_deque_data;

	static size_t		_comparison_count;

	void	parseArguments( int argc, char **argv );
	void	printBefore( void ) const;
	void	printAfter( void ) const;
	void	printTiming( const std::string &name, size_t size, clock_t duration ) const;
	void	printComparisons( const std::string &name, size_t comparisons ) const;

	static int		parsePositiveInteger( const std::string &token );
	static bool		_comp( const Element &lhs, const Element &rhs );
	static size_t	jacobsthal( size_t index );
	static void		resetComparisonCount( void );
	static size_t	getComparisonCount( void );

	static std::vector<Element>	makeElements( const std::vector<int> &values );
	static std::vector<Element>	makeElements( const std::deque<int> &values );
	static std::vector<size_t>	makeInsertionOrder( size_t pending_size );
	static std::vector<Element>	mergeInsertionSort( const std::vector<Element> &input );

	template <typename Container>
	static void	sortContainer( Container &container );
	template <typename Container>
	static bool	isSorted( const Container &container );

	static std::vector<Element>::iterator	findById( std::vector<Element> &chain, size_t id );
};

template <typename Container>
void	PmergeMe::sortContainer( Container &container ) {
	std::vector<Element>	elements = makeElements(container);
	std::vector<Element>	sorted = mergeInsertionSort(elements);

	for (size_t i = 0; i < sorted.size(); i++)
		container[i] = sorted[i].value;
}

template <typename Container>
bool	PmergeMe::isSorted( const Container &container ) {
	for (size_t i = 1; i < container.size(); i++) {
		if (container[i] < container[i - 1])
			return false;
	}
	return true;
}
