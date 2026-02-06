#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <victim_pid>" << std::endl;
		return 1;
	}
	
	pid_t victim_pid = atoi(argv[1]);
	
	std::cout << "=== Attacker Program ===" << std::endl;
	std::cout << "Target PID: " << victim_pid << std::endl;
	std::cout << std::endl;
	
	std::cout << "Attempting to attach to victim process..." << std::endl;
	
	// محاولة الاتصال بالـ process
	if (ptrace(PTRACE_ATTACH, victim_pid, NULL, NULL) == -1) {
		std::cerr << "✗ Failed to attach: " << strerror(errno) << std::endl;
		std::cerr << std::endl;
		std::cerr << "Reasons:" << std::endl;
		std::cerr << "  1. No permission (need same user or root)" << std::endl;
		std::cerr << "  2. ptrace protection enabled" << std::endl;
		std::cerr << "  3. Process doesn't exist" << std::endl;
		std::cerr << std::endl;
		std::cerr << "Try: echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope" << std::endl;
		return 1;
	}
	
	waitpid(victim_pid, NULL, 0);
	std::cout << "✓ Attached successfully!" << std::endl;
	std::cout << "Now we have access to victim's memory!" << std::endl;
	std::cout << std::endl;
	
	// نقراو شي حاجة من memory ديالو
	std::cout << "(Reading victim's memory would happen here...)" << std::endl;
	std::cout << std::endl;
	
	// نحررو الضحية
	ptrace(PTRACE_DETACH, victim_pid, NULL, NULL);
	std::cout << "✓ Detached from victim" << std::endl;
	std::cout << std::endl;
	std::cout << "This demonstrates that cross-process access" << std::endl;
	std::cout << "requires special permissions and tools!" << std::endl;
	
	return 0;
}
