#include <iostream>
#include <fstream>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

// الدالة لي بغينا نستدعيوها من برنامج آخر
void myFunction() {
	std::cout << "🎯 SUCCESS! Function called from another program!" << std::endl;
}

int main() {
	std::cout << "=== Program 1: Function Provider ===" << std::endl;
	std::cout << std::endl;
	
	// نجيبو عنوان الدالة
	void (*funcPtr)() = &myFunction;
	uintptr_t address = reinterpret_cast<uintptr_t>(funcPtr);
	
	std::cout << "Function address: " << address << std::endl;
	std::cout << "PID: " << getpid() << std::endl;
	std::cout << std::endl;
	
	// نكتبو العنوان والـ PID في ملف
	std::ofstream file("func_info.txt");
	file << getpid() << std::endl;
	file << address;
	file.close();
	
	std::cout << "Function info saved to func_info.txt" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Testing function locally:" << std::endl;
	myFunction();
	std::cout << std::endl;
	
	std::cout << "Program will stay alive for 60 seconds..." << std::endl;
	std::cout << "Run program2 in another terminal NOW!" << std::endl;
	std::cout << std::endl;
	
	// نبقاو حيين باش البرنامج الآخر يلقانا
	for (int i = 60; i > 0; i--) {
		std::cout << "\rTime remaining: " << i << " seconds   " << std::flush;
		sleep(1);
	}
	std::cout << std::endl << std::endl;
	std::cout << "Program 1 exiting..." << std::endl;
	
	return 0;
}
