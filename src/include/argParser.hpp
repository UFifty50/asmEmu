#ifndef argParser_hpp
#define argParser_hpp

#include <vector>
#include <string>
#include <functional>


union passableArgs {
    std::string s;
    std::nullptr_t v;
};

struct arg {
    std::string name;
    std::string alias;
    std::string description;
    bool required;
    bool requiresInput;
    std::function<void(passableArgs)> callback;
};

class argParser {
private:
    std::vector<std::string> args;
    std::vector<arg> argList;
    bool defaultHelp;
    void constructDefaultHelp();

public:
    argParser(int argc, char** argv, bool defaultHelp = true);

    void registerShortArg(char shortArg, std::string description, bool required, bool requiresInput, std::function<void(passableArgs)> function);
    void registerLongArg(std::string longArg, std::string description, bool required, bool requiresInput, std::optional<std::function<void(std::string)>> function = std::nullopt, std::string alias = "");

    void parse();
};

#endif
