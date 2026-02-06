# Cross-process tests (will fail - demonstration)
cross_process: program1 program2

program1: program1.cpp
	c++ -Wall -Wextra -Werror -std=c++98 program1.cpp -o program1

program2: program2.cpp
	c++ -Wall -Wextra -Werror -std=c++98 program2.cpp -o program2

# Victim and Attacker (ptrace demonstration)
attack_demo: victim attacker

victim: victim.cpp
	c++ -Wall -Wextra -Werror -std=c++98 victim.cpp -o victim

attacker: attacker.cpp
	c++ -Wall -Wextra -Werror -std=c++98 attacker.cpp -o attacker

# Shared library solution (will work!)
shared_lib: libshared.so programA programB

libshared.so: sharedLib.cpp
	c++ -shared -fPIC sharedLib.cpp -o libshared.so

programA: programA.cpp
	c++ -Wall -Wextra -Werror -std=c++98 programA.cpp -o programA -ldl

programB: programB.cpp
	c++ -Wall -Wextra -Werror -std=c++98 programB.cpp -o programB -ldl

all: cross_process shared_lib attack_demo

clean:
	rm -f program1 program2 programA programB victim attacker libshared.so func_info.txt *.o

re: clean all

test_cross:
	@echo "Testing cross-process (will fail):"
	@timeout 5 ./program1 & sleep 1 && ./program2 || true

test_shared:
	@echo "Testing shared library (will work):"
	@./programA
	@echo ""
	@./programB

.PHONY: all clean re cross_process shared_lib test_cross test_shared
