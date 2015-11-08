#include <iostream>
#include <string>
#include "CliInputHelper.h"
#include "Parser.hpp"
#include "BlockExporter.h"

int main(int argc, char** argv)
{
    IrLibPlus::Parser parser{};
    IrLibPlus::BlockExporter exporter;
    IrLibPlus::CliInputHelper cliInputHelper(
        argc, std::vector<std::string>(argv, argv + argc));

    std::string input = cliInputHelper.getInput();
    if (input.size() < 1) {
        std::cout << cliInputHelper.getHelp();
        return 0;
    }

    std::string outputPath = cliInputHelper.getOutputFilePath();
    if (outputPath.size()) {
        exporter.exportBlockStreamToFilePath(parser.parse(input), outputPath);
    } else {
        std::cout << exporter.exportBlockStream(parser.parse(input));
    }

    return 0;
}
