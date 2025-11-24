#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie {
    private:
        std::string name;

    public:

    Zombie();
    int index;
    void set_name( std::string zname);
    void announce( void );
    ~Zombie(){
        std::cout << name << index << " destroyed" << std::endl;
    }
};

Zombie* zombieHorde( int N, std::string name );

#endif