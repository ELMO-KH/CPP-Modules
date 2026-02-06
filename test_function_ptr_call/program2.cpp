#include <iostream>
#include <fstream>
#include <stdint.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	std::cout << "=== Program 2: Function Caller ===" << std::endl;
	std::cout << std::endl;
	
	// نقراو معلومات الدالة
	std::ifstream file("func_info.txt");
	if (!file.is_open()) {
		std::cerr << "Error: func_info.txt not found!" << std::endl;
		std::cerr << "Make sure program1 is running first!" << std::endl;
		return 1;
	}
	
	pid_t target_pid;
	uintptr_t func_address;
	file >> target_pid >> func_address;
	file.close();
	
	std::cout << "Target PID: " << target_pid << std::endl;
	std::cout << "Function address: " << func_address << std::endl;
	std::cout << std::endl;
	
	std::cout << "⚠️  NOTE: Cross-process function calls are blocked by Linux!" << std::endl;
	std::cout << "Reasons:" << std::endl;
	std::cout << "  1. Memory isolation (ASLR)" << std::endl;
	std::cout << "  2. Security (process cannot access other's memory)" << std::endl;
	std::cout << "  3. Different address spaces" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Attempting to call anyway (will likely fail)..." << std::endl;
	std::cout << std::endl;
	
	// محاولة استدعاء (غالباً ستفشل)
	void (*funcPtr)() = reinterpret_cast<void(*)()>(func_address);
	
	std::cout << "Calling function at address " << func_address << "..." << std::endl;
	
	// هذا سيسبب segmentation fault غالباً
	try {
		funcPtr();
		std::cout << "✓ Somehow it worked! (unlikely)" << std::endl;
	} catch (...) {
		std::cout << "✗ Failed as expected!" << std::endl;
	}
	
	return 0;
}
