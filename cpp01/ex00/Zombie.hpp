#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie {
    private:
        std::string name;
    public:
        Zombie();
        void set_name( std::string zname);
        void announce( void );
        ~Zombie(){
            std::cout << name << " destroyed" << std::endl;
        }
};

Zombie* newZombie( std::string name );
void randomChump( std::string name );
#endif