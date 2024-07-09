#ifndef HEXDUMPER_HPP
#define HEXDUMPER_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

class Hexdumper {
public:
    Hexdumper();
    ~Hexdumper();
    void Hexdump(const std::string &file, const std::string &output_file = "");
};

#endif // !HEXDUMPER_HPP
