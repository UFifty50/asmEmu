#include <vector>
#include <string>
#include <functional>
#include <iostream>

#include "argParser.hpp"

argParser::argParser(int argc, char** argv, bool defaultHelp) : defaultHelp(defaultHelp) {
    // copy command line arguments into a vector
    if (argc > 0) args.assign(argv, argv+argc);
}

void argParser::constructDefaultHelp() {
    std::cout << args.at(args.size()-1) << std::endl;
    std::cout << "Command\talias\tdescription\t\t\trequired" << std::endl;
    for (auto arg : this->argList) {
        std::cout << arg.name << "\t" << arg.alias << "\t" << arg.description << "\t" << (arg.required ? "true" : "false") << std::endl;
    }
}

void argParser::registerShortArg(char shortArg, std::string description, bool required, std::function<void(std::string)> function) {
    arg a;
    a.name = std::string("-") + shortArg;
    a.description = description;
    a.required = required;
    a.callback = function;
    argList.push_back(a);
}

void argParser::registerLongArg(std::string shortArg, std::string description, bool required, std::function<void(std::string)> function, std::string alias) {
    arg a;
    a.name = "--" + shortArg;
    a.description = description;
    a.required = required;
    a.callback = function;
    if (alias != "") a.alias = "-" + alias;
    argList.push_back(a);
}

void argParser::parse() {
    if (defaultHelp) registerLongArg("help", "Displays this help message", false, [this](std::string x) { this->constructDefaultHelp(); }, "h");
    
    std::sort(args.begin(), args.end());
    args.erase(std::unique(args.begin(), args.end()), args.end());
    for (auto i : args) {
        for (auto a : argList) {
            if (i == a.name || i == a.alias) {
                a.callback(args[std::find(args.begin(), args.end(), i) - args.begin() +1]);
            }
        }
    }
}
