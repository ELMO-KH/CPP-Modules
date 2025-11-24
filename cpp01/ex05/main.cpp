#include "Harl.hpp"

int main(void){
    
    Harl harl;
    void (Harl::*ptr)(std::string) = &Harl::complain;
    (harl.*ptr)("DEBUG");
    
}