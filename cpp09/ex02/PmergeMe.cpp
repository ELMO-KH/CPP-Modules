#include "PmergeMe.hpp"

#include <algorithm>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <stdexcept>

size_t	PmergeMe::_comparison_count = 0;

PmergeMe::Element::Element( void ) : value(0), id(0) {}

PmergeMe::Element::Element( int value, size_t id ) : value(value), id(id) {}

PmergeMe::Pair::Pair( const Element &first, const Element &second ) :
	small(first),
	large(second) {
	if (_comp(large, small))
		std::swap(small, large);
}

PmergeMe::Pending::Pending( const Element &value, size_t bound_id ) :
	value(value),
	bound_id(bound_id),
	has_bound(true) {}

PmergeMe::Pending::Pending( const Element &value ) :
	value(value),
	bound_id(0),
	has_bound(false) {}

PmergeMe::PmergeMe( void ) {}

PmergeMe::PmergeMe( const PmergeMe &other ) {
	*this = other;
}

PmergeMe &PmergeMe::operator=( const PmergeMe &other ) {
	if (this != &other) {
		_vector_data = other._vector_data;
		_deque_data = other._deque_data;
	}
	return *this;
}

PmergeMe::~PmergeMe( void ) {}

void	PmergeMe::run( int argc, char **argv ) {
	clock_t	start;
	clock_t	vector_time;
	clock_t	deque_time;
	// size_t	vector_comparisons;
	// size_t	deque_comparisons;

	parseArguments(argc, argv);
	// if (isSorted(_vector_data)) {
	// 	std::cout << "Already sorted" << std::endl;
	// 	return ;
	// }
	printBefore();

	resetComparisonCount();
	start = clock();
	sortContainer(_vector_data);
	vector_time = clock() - start;
	// vector_comparisons = getComparisonCount();

	resetComparisonCount();
	start = clock();
	sortContainer(_deque_data);
	deque_time = clock() - start;
	// deque_comparisons = getComparisonCount();

	printAfter();
	printTiming("std::vector", _vector_data.size(), vector_time);
	printTiming("std::deque", _deque_data.size(), deque_time);
	// printComparisons("std::vector", vector_comparisons);
	// printComparisons("std::deque", deque_comparisons);
}

void	PmergeMe::parseArguments( int argc, char **argv ) {
	for (int i = 1; i < argc; i++) {
		std::istringstream	stream(argv[i]);
		std::string			token;

		while (stream >> token) {
			int	value = parsePositiveInteger(token);

			_vector_data.push_back(value);
			_deque_data.push_back(value);
		}
		if (stream.bad())
			throw std::invalid_argument("Error");
	}
	if (_vector_data.empty())
		throw std::invalid_argument("Error");
}

void	PmergeMe::printBefore( void ) const {
	std::cout << "Before:";
	for (std::vector<int>::const_iterator it = _vector_data.begin(); it != _vector_data.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void	PmergeMe::printAfter( void ) const {
	std::cout << "After:";
	for (std::vector<int>::const_iterator it = _vector_data.begin(); it != _vector_data.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void	PmergeMe::printTiming( const std::string &name, size_t size, clock_t duration ) const {
	double	microseconds = static_cast<double>(duration) * 1000000.0 / CLOCKS_PER_SEC;

	std::cout << "Time to process a range of " << size << " elements with " << name
		<< " : " << std::fixed << std::setprecision(5) << microseconds << " us" << std::endl;
}

void	PmergeMe::printComparisons( const std::string &name, size_t comparisons ) const {
	std::cout << "Comparisons made with " << name << " : " << comparisons << std::endl;
}

int	PmergeMe::parsePositiveInteger( const std::string &token ) {
	char	*end;
	long	value;

	if (token.empty())
		throw std::invalid_argument("Error");
	for (size_t i = 0; i < token.length(); i++) {
		if (i == 0 && token[i] == '+')
			continue;
		if (token[i] < '0' || token[i] > '9')
			throw std::invalid_argument("Error");
	}
	errno = 0;
	value = std::strtol(token.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE || value < 0 || value > INT_MAX)
		throw std::invalid_argument("Error");
	return static_cast<int>(value);
}

void	PmergeMe::resetComparisonCount( void ) {
	_comparison_count = 0;
}

size_t	PmergeMe::getComparisonCount( void ) {
	return _comparison_count;
}

size_t	PmergeMe::jacobsthal( size_t index ) {
	size_t	previous = 0;
	size_t	current = 1;

	if (index == 0)
		return 0;
	for (size_t i = 1; i < index; i++) {
		size_t	next = current + (2 * previous);

		previous = current;
		current = next;
	}
	return current;
}

std::vector<PmergeMe::Element>
PmergeMe::makeElements( const std::vector<int> &values ) {
	std::vector<Element>	elements;

	elements.reserve(values.size());
	for (size_t i = 0; i < values.size(); i++)
		elements.push_back(Element(values[i], i));
	return elements;
}

std::vector<PmergeMe::Element>
PmergeMe::makeElements( const std::deque<int> &values ) {
	std::vector<Element>	elements;

	elements.reserve(values.size());
	for (size_t i = 0; i < values.size(); i++)
		elements.push_back(Element(values[i], i));
	return elements;
}

std::vector<size_t>	PmergeMe::makeInsertionOrder( size_t pending_size ) {
	std::vector<size_t>	order;
	size_t				previous;
	size_t				current;
	size_t				jacobsthal_index;

	if (pending_size == 0)
		return order;
	order.reserve(pending_size);
	previous = 1;
	jacobsthal_index = 3;
	current = jacobsthal(jacobsthal_index);
	while (order.size() < pending_size) {
		size_t	end = current - 1;
		size_t	index;

		if (end > pending_size)
			end = pending_size;
		index = end;
		while (index >= previous) {
			order.push_back(index - 1);
			if (index == previous)
				break;
			index--;
		}
		previous = current;
		jacobsthal_index++;
		current = jacobsthal(jacobsthal_index);
	}
	return order;
}

std::vector<PmergeMe::Element>
PmergeMe::mergeInsertionSort( const std::vector<Element> &input ) {
	std::vector<Pair>		pairs;
	std::vector<Element>		largers;
	std::vector<Element>		sorted_largers;
	std::vector<Element>		main_chain;
	std::vector<Pending>		pending;
	std::vector<size_t>		order;
	bool					has_stray;
	Element					stray;

	if (input.size() < 2)
		return input;
	pairs.reserve(input.size() / 2);
	largers.reserve(input.size() / 2);
	has_stray = (input.size() % 2 != 0);
	for (size_t i = 0; i + 1 < input.size(); i += 2) {
		pairs.push_back(Pair(input[i], input[i + 1]));
		largers.push_back(pairs.back().large);
	}
	if (has_stray)
		stray = input.back();
	sorted_largers = mergeInsertionSort(largers);
	main_chain = sorted_largers;
	if (sorted_largers.empty())
		return input;
	for (size_t i = 0; i < sorted_largers.size(); i++) {
		for (size_t j = 0; j < pairs.size(); j++) {
			if (pairs[j].large.id == sorted_largers[i].id) {
				if (i == 0)
					main_chain.insert(main_chain.begin(), pairs[j].small);
				else
					pending.push_back(Pending(pairs[j].small, pairs[j].large.id));
				break;
			}
		}
	}
	if (has_stray)
		pending.push_back(Pending(stray));
	order = makeInsertionOrder(pending.size());
	for (size_t i = 0; i < order.size(); i++) {
		Pending							&entry = pending[order[i]];
		std::vector<Element>::iterator	bound = main_chain.end();
		std::vector<Element>::iterator	position;

		if (entry.has_bound)
			bound = findById(main_chain, entry.bound_id);
		position = std::upper_bound(main_chain.begin(), bound, entry.value, _comp);
		main_chain.insert(position, entry.value);
	}
	return main_chain;
}

bool	PmergeMe::_comp( const Element &lhs, const Element &rhs ) {
	_comparison_count++;
	return lhs.value < rhs.value;
}

std::vector<PmergeMe::Element>::iterator
PmergeMe::findById( std::vector<Element> &chain, size_t id ) {
	for (std::vector<Element>::iterator it = chain.begin(); it != chain.end(); ++it) {
		if (it->id == id)
			return it;
	}
	return chain.end();
}
