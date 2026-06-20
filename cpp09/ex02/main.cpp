# include "PmergeMe.hpp"

int	check = 0;

int	main(int arc, char **arv) {

	if (arc == 1) {
		std::cerr << "ERROR";
		std::endl(std::cerr);
		return 1;
	}
	try {
		PmergeMe	PmergeMe_;

		PmergeMe_.hanleArgument(arv);
	}catch ( std::exception &e ) {
		std::cerr << "ERROR: " << e.what();
		std::endl(std::cerr);
		return 1;
	}
	return 0;
}