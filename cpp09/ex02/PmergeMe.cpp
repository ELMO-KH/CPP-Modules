
# include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ) {}

PmergeMe::PmergeMe( const  PmergeMe &Other ) {
	*this = Other;
}

PmergeMe &PmergeMe::operator=( const PmergeMe &Other ) {
	if (this != &Other) {
		this->_vectorData = Other._vectorData;
		this->_dequeData = Other._dequeData;
	}
	return *this;
}

PmergeMe::~PmergeMe( void ) {}

bool	PmergeMe::IsDigit( std::string &str) {

	short	i = 0;
	if (str[i] == '+') i = 1;
	for (; str[i]; i++) {
		if (!std::isdigit(str[i])) return false;
	}
	return true;
}

void	PmergeMe::PrintBefor(){
	std::cout << "Before : ";
	for (_it it = _vectorData.begin(); it != _vectorData.end(); it++)
		std::cout << *it << " " ;
	std::endl(std::cout);
}

void	printVector(std::vector<int>vec) {
	static int Level = 1;
	std::cout << "Pair Level: " << Level++ << std::endl;
	for (_it i = vec.begin(); i != vec.end(); i++)
		std::cout << " " << *i ;
	std::cout << std::endl;

}

void	PmergeMe::PrintAfter( void ) {

	std::cout << "After : ";
	for (_it it = _vectorData.begin(); it != _vectorData.end(); it++)
		std::cout << *it << " " ;
	std::endl(std::cout);
}

size_t	GeneratJacobsthalNumber(size_t k) {
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

void	PrintStatusContainer( std::vector<int> &Container, clock_t duration ){
	std::cout.precision(6);
	double seconds = (double)duration / CLOCKS_PER_SEC;
	double microseconds = seconds * 1000000; 
	std::cout << "Time to process a range of " << Container.size() <<" elements with std::[..] : " << std::fixed << microseconds << " us" << std::endl;
}

void	PmergeMe::sort( void ) {

	if (_vectorData.size() == 1) {
		return ;
	}

	clock_t startTimeVector, endTimeVector;
	startTimeVector = clock();
	PairingPhase(_vectorData, 1);
	endTimeVector = clock() - startTimeVector;
	PrintAfter();
	PrintStatusContainer(_vectorData, endTimeVector);

	clock_t	startTimeDeque, endTimeDeque;
	startTimeDeque	= clock();
	PairingPhase(_dequeData, 1);
	endTimeDeque = clock() - startTimeDeque;
	PrintStatusContainer(_dequeData, endTimeDeque);
}

void	PmergeMe::hanleArgument( char **const arv) {

	std::set<int>	set_;
	for (int index = 1; arv[index]; index++) {
		std::istringstream	ss(arv[index]);
		while (!ss.eof()) {
			std::string		token;
			ss >> token;
			if (token.empty())
				throw std::invalid_argument("Argument is Empty");
			if (std::string("0123456789+-").find(token[0]) == std::string::npos)
        			throw std::invalid_argument("Arguments is invalid");
			if (token[0] == '-') 
				throw std::invalid_argument("Argument Is Negative");
			if (!IsDigit(token))
				throw std::invalid_argument("An Argument is invalid");
			std::pair<std::set<int>::iterator, bool> check = set_.insert(std::atoi(token.c_str()));
		        if (check.second == false)
                		throw std::invalid_argument("Some Duplicate Found");
			this->_vectorData.push_back(std::atoi(token.c_str()));
			this->_dequeData.push_back(std::atoi(token.c_str()));
		}
	}
	PrintBefor();
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
