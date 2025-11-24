#ifndef SED_HPP
#define SED_HPP

#include <string>
#include <fstream>
#include <iostream>

class Sed {
    private:
        std::string filename;
    public:
        Sed(std::string filename);
        void replace(std::string s1, std::string s2);
};

#endif