#include <iostream>
#include <unistd.h>

void secretFunction() {
	std::cout << "🔒 This is a SECRET function!" << std::endl;
}

int main() {
	std::cout << "=== Victim Program ===" << std::endl;
	std::cout << "PID: " << getpid() << std::endl;
	std::cout << "secretFunction address: " << (void*)&secretFunction << std::endl;
	std::cout << std::endl;
	std::cout << "I will NOT share my function with anyone!" << std::endl;
	std::cout << "Sleeping forever..." << std::endl;
	std::cout << std::endl;
	
	// نبقاو نعيشو
	while (true) {
		sleep(10);
	}
	
	return 0;
}
