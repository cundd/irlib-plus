#include <string>
#include <sstream>
#include <iostream>

namespace IrLibPlus {
    class CliInputHelper {
    public:
        inline std::string getInput(int argc, char** argv) {
            if (argc > 1) {
                return argv[1];
            }
            return getInputFromStdIn();
        }

    private:
        inline std::string getInputFromStdIn() {
            std::stringstream input;
            std::string currentLine;
            while (std::getline(std::cin, currentLine))
            {
                input << currentLine;
            }

            return input.str();
        }
    };
}
