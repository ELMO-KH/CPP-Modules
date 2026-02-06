#include <iostream>
#include <dlfcn.h>
#include <stdint.h>

int main() {
	std::cout << "=== Program A: Loading shared library ===" << std::endl;
	std::cout << std::endl;
	
	// نحملو المكتبة
	void* handle = dlopen("./libshared.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Error: " << dlerror() << std::endl;
		return 1;
	}
	
	// نجيبو عنوان الدالة
	typedef void (*FuncPtr)();
	FuncPtr func = (FuncPtr)dlsym(handle, "sharedFunction");
	if (!func) {
		std::cerr << "Error: " << dlerror() << std::endl;
		dlclose(handle);
		return 1;
	}
	
	uintptr_t address = reinterpret_cast<uintptr_t>(func);
	std::cout << "Function address: " << address << std::endl;
	std::cout << std::endl;
	
	std::cout << "Calling function:" << std::endl;
	func();
	std::cout << std::endl;
	
	dlclose(handle);
	std::cout << "✓ Program A done!" << std::endl;
	return 0;
}
