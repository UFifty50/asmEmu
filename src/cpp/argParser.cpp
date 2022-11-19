#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <optional>

#include "argParser.hpp"

argParser::argParser(int argc, char** argv, bool defaultHelp) : defaultHelp(defaultHelp) {
    // copy command line arguments into a vector
    if (argc > 0) args.assign(argv+1, argv+argc); // skip the program name
    if (defaultHelp) registerLongArg("help", "Displays this help message", false, false, [this]() { this->constructDefaultHelp(); }, "h"); 
}

void argParser::constructDefaultHelp() {
    if (args.size() < 1) {
        std::cerr << "Error: No arguments provided." << std::endl;
        return;
    }
    std::cout << args.at(args.size()-1) << std::endl;
    std::cout << "Command\talias\tdescription\t\t\trequired" << std::endl;
    for (auto arg : this->argList) {
        std::cout << arg.name << "\t" << arg.alias << "\t" << arg.description << "\t" << (arg.required ? "true" : "false") << std::endl;
    }
}

void argParser::registerShortArg(char shortArg, std::string description, bool required, bool requiresInput, std::function<void(passableArgs)> function) {
    arg a;
    a.name = std::string("-") + shortArg;
    a.description = description;
    a.required = required;
    a.requiresInput = requiresInput;
    a.callback = function;
    argList.push_back(a);
}

void argParser::registerLongArg(std::string longArg, std::string description, bool required, bool requiresInput, std::function<void(passableArgs)> function, std::string alias) {
    arg a;
    a.name = "--" + longArg;
    a.description = description;
    a.required = required;
    a.requiresInput = requiresInput;
    a.callback = function;
    if (alias != "") a.alias = "--" + alias;
    argList.push_back(a);
}

void argParser::parse() {
    std::sort(args.begin(), args.end()); // Sorts the arguments vector
    args.erase(std::unique(args.begin(), args.end()), args.end()); // Removes duplicates
    for (auto i : args) {
        for (auto a : argList) {
            if (i == a.name || i == a.alias) {
                if (a.requiresInput) {
                    if (std::find(args.begin(), args.end(), i) + 1 != args.end()) { // This line checks if the current argument is not the last argument in the vector
                        a.callback(args[std::find(args.begin(), args.end(), i) - args.begin() +1]); // Calls the callback function with the next argument. This is used for arguments like -i input.txt
                    }
                } else a.callback(); // Calls the callback function without any input. This is used for arguments like -h
            }
        }
    }
}
