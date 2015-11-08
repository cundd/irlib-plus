#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace IrLibPlus
{
class CliInputHelper
{
    int argumentsCount;
    std::vector<std::string> arguments;

public:
    CliInputHelper(int argumentsCount, std::vector<std::string>&& arguments)
        : argumentsCount(argumentsCount), arguments(arguments)
    {
    }

    inline std::string getInput()
    {
        if (argumentsCount == 2 || argumentsCount > 3) {
            return arguments[argumentsCount - 1];
        }
        return getInputFromStdIn();
    }

    inline std::string getOutputFilePath()
    {
        // path/to/irlib-plus -o output/file/path
        // path/to/irlib-plus --output output/file/path
        // path/to/irlib-plus -o output/file/path inputString
        // path/to/irlib-plus --output output/file/path inputString
        if (argumentsCount > 3) {
            if (arguments[1] == "-o" || arguments[1] == "--output") {
                return arguments[2];
            }
        }
        return "";
    }

    const std::string& getHelp()
    {
        static std::string help = "Usage: irlib-plus [options] [inputString]\n"
                                  "Options:\n"
                                  "-o FILE, --output FILE   Output file path\n";
        return help;
    }

private:
    inline std::string getInputFromStdIn()
    {
        std::stringstream input;
        std::string currentLine;
        while (std::getline(std::cin, currentLine)) {
            input << currentLine;
        }

        return input.str();
    }
};
}
