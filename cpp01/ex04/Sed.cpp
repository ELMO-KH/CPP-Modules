#include "Sed.hpp"

Sed::Sed(std::string filename) : filename(filename) {
}

void Sed::replace(std::string s1, std::string s2) {
    std::ifstream inputfile(this->filename.c_str());
    if (!inputfile.is_open()) {
        std::cerr << "Error: Could not open the file" << std::endl;
        return;
    }

    std::string content;
    std::string buffer;
    
    if (std::getline(inputfile, buffer)) {
        content = buffer;
        while (std::getline(inputfile, buffer)) {
            content += "\n" + buffer;
        }
    }
    inputfile.close();

    if (s1.empty()) {
        std::ofstream outfile((this->filename + ".replace").c_str());
        outfile << content;
        outfile.close();
        return;
    }

    size_t pos = 0;
    while (true) {
        pos = content.find(s1, pos);
        if (pos == std::string::npos)
            break;
        content.erase(pos, s1.length());
        content.insert(pos, s2);
        pos += s2.length();
    }

    std::ofstream outfile((this->filename + ".replace").c_str());
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not create the file" << std::endl;
        return;
    }
    outfile << content;
    outfile.close();
}