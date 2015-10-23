#include <iostream>
#include <string>
#include "CliInputHelper.h"
#include "Parser.hpp"
#include "BlockExporter.h"

int main(int argc, char** argv)
{
    IrLibPlus::Parser parser{};
    IrLibPlus::BlockExporter exporter;
    IrLibPlus::CliInputHelper cliInputHelper;

    // if (argc < 2) {
    //
    //     std::cerr << "Missing input" << std::endl;
    //     return 1;
    // }
    std::string input = cliInputHelper.getInput(argc, argv);
    std::cout << exporter.exportBlockStream(parser.parse(input));

    return 0;
}
