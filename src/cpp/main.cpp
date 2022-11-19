#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

#include "argParser.hpp"


int main(int argc, char** argv) {
    std::ifstream f;
    argParser parser(argc, argv, true);
    parser.registerShortArg('i', "Input file to compile into a ROM", false, [&f](std::string in) { f = std::ifstream(in); });
    parser.parse();
    std::string str;
    if(f) {
        std::ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }
    std::cout << str;
    return 1;
}
