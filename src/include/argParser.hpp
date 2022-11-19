#ifndef argParser_hpp
#define argParser_hpp

#include <vector>
#include <string>
#include <functional>


struct arg {
    std::string name;
    std::string alias;
    std::string description;
    bool required;
    std::function<void(std::string)> callback;
};

class argParser {
private:
    std::vector<std::string> args;
    std::vector<arg> argList;
    bool defaultHelp;
    void constructDefaultHelp();

public:
    argParser(int argc, char** argv, bool defaultHelp = true);

    void registerShortArg(char shortArg, std::string description, bool required, std::function<void(std::string)> function);
    void registerLongArg(std::string shortArg, std::string description, bool required, std::function<void(std::string)> function, std::string alias = "");

    void parse();
};

#endif
