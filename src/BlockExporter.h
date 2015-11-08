//
//  BlockExporter.h
//  irlib-plus
//
//  Created by Daniel Corn on 27.09.15.
//
//

#ifndef __irlib_plus__BlockExporter__
#define __irlib_plus__BlockExporter__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Block.hpp"

namespace IrLibPlus
{
class BlockExporter
{
public:
    std::string exportBlockStream(const IrLibPlus::BlockStream& blockStream)
    {
        const std::string jsNamespace = "IrLib.View.Parser";
        std::stringstream blockContent;
        blockContent << "[";
        blockContent << "\n";

        for (auto const& block : blockStream) {
            blockContent
                << "new " << jsNamespace << "."
                << "Block(" << jsNamespace << "."
                << "BlockType."
                << BlockTypeUtility::string(
                       block.type()) //<< static_cast<int>(block.type())
                << ", "
                << "\"" << block.content() << "\""
                << ", "
                << "{"
                << "isSafe:" << (block.isSafe() ? "true" : "false") << ", "
                << "expressionType:" << jsNamespace << "."
                << "ExpressionType."
                << ExpressionTypeUtility::string(
                       block
                           .expressionType()) //<<
                                              //static_cast<int>(block.expressionType())
                << "}"
                << ")";

            if (&block != &blockStream.back()) {
                blockContent << ", ";
            }

            blockContent << "\n";
        }

        blockContent << "]";
        blockContent << "\n";

        return blockContent.str();
    }

    bool exportBlockStreamToFilePath(const IrLibPlus::BlockStream& blockStream,
                                     std::string& filePath)
    {
        std::ofstream outputFile;
        outputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            outputFile.open(filePath);
            outputFile << exportBlockStream(blockStream);
        } catch (std::ofstream::failure& writeError) {
            std::cerr << "Error while writing to output file: "
                      //   << writeError.what()
                      //   << "\n"
                      << strerror(errno) << std::endl;
            return false;
        }

        return true;
    }
};
}

#endif /* defined(__irlib_plus__BlockExporter__) */
