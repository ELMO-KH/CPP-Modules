#include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ) {}

PmergeMe::PmergeMe( const PmergeMe &other ) {
	*this = other;
}

PmergeMe &PmergeMe::operator=( const PmergeMe &other ) {
	if (this != &other) {
		this->_vectorData = other._vectorData;
		this->_dequeData = other._dequeData;
	}
	return *this;
}

PmergeMe::~PmergeMe( void ) {}

bool	PmergeMe::isPositiveNumber( const std::string &token ) const {

	size_t	i = 0;

	if (token.empty())
		return false;
	if (token[i] == '+')
		i++;
	if (i == token.length())
		return false;
	for (; i < token.length(); i++) {
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			return false;
	}
	return true;
}

void	PmergeMe::printBefore( void ) const {

	std::cout << "Before : ";
	for (std::vector<int>::const_iterator it = _vectorData.begin(); it != _vectorData.end(); it++)
		std::cout << *it << " " ;
	std::endl(std::cout);
}

void	PmergeMe::printAfter( void ) const {

	std::cout << "After : ";
	for (std::vector<int>::const_iterator it = _vectorData.begin(); it != _vectorData.end(); it++)
		std::cout << *it << " " ;
	std::endl(std::cout);
}

size_t	generateJacobsthalNumber(size_t k) {
	if (k == 0) return 0;
	if (k == 1) return 1;

	size_t prev2 = 0, prev1 = 1;
	for (size_t i = 2; i <= k; i++) {
		size_t result = prev1 + 2 * prev2;
		prev2 = prev1;
		prev1 = result;
	}
	return prev1;
}

void	PmergeMe::sort( void ) {

	if (_vectorData.size() == 1)
		return ;

	clock_t	start_time;
	clock_t	vector_duration;
	clock_t	deque_duration;

	start_time = clock();
	pairingPhase(_vectorData, 1);
	vector_duration = clock() - start_time;
	printAfter();
	printStatus(_vectorData, vector_duration);

	start_time = clock();
	pairingPhase(_dequeData, 1);
	deque_duration = clock() - start_time;
	printStatus(_dequeData, deque_duration);
}

void	PmergeMe::handleArguments( char **const argv ) {

	std::set<int>	set_;

	for (int index = 1; argv[index]; index++) {
		std::istringstream	ss(argv[index]);
		std::string			token;

		while (ss >> token) {
			if (token[0] == '-')
				throw std::invalid_argument("Argument Is Negative");
			if (!isPositiveNumber(token))
				throw std::invalid_argument("An Argument is invalid");

			std::pair<std::set<int>::iterator, bool> check = set_.insert(std::atoi(token.c_str()));
			if (check.second == false)
				throw std::invalid_argument("Some Duplicate Found");

			this->_vectorData.push_back(std::atoi(token.c_str()));
			this->_dequeData.push_back(std::atoi(token.c_str()));
		}
		if (ss.bad())
			throw std::invalid_argument("Arguments is invalid");
	}
	printBefore();
	sort();

	bool sorted = true;
	for (size_t i = 1; i < _vectorData.size(); i++) {
		if (_vectorData[i] < _vectorData[i-1]) {
			sorted = false;
			break;
		}
	}

	std::cout << "\nVerification: " << (sorted ? "✓ CORRECTLY SORTED" : "✗ NOT SORTED") << std::endl;
	std::cout << "Total comparisons made: " << check / 2 << std::endl;
}

void	PmergeMe::hanleArgument( char **const argv ) {
	handleArguments(argv);
}
