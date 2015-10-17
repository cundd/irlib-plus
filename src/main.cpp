#include <iostream>
#include <string>
#include "Parser.hpp"
#include "BlockExporter.h"

int main(int argc, char** argv)
{
    IrLibPlus::Parser parser{};
    IrLibPlus::BlockExporter exporter;

    if (argc < 2) {
        std::cerr << "Missing input" << std::endl;
        return 1;
    }

    std::cout << exporter.exportBlockStream(parser.parse(argv[1]));

    return 0;
}
