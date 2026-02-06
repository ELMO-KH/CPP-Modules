#include <iostream>

extern "C" {
	void sharedFunction() {
		std::cout << "🎯 SUCCESS! Called from shared library!" << std::endl;
		std::cout << "This works across different programs!" << std::endl;
	}
}
