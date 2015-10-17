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
#include <sstream>
#include <iomanip>
#include "Block.hpp"

namespace IrLibPlus {

class BlockExporter {
public:
    std::string exportBlockStream(const IrLibPlus::BlockStream& blockStream)
    {
        std::stringstream blockContent;
        blockContent << "[";
        blockContent << "\n";
        std::cout << "\n";

        for (auto const& block : blockStream) {

            blockContent << "new Block("
                         << "BlockType." << BlockTypeUtility::string(block.type()) //<< static_cast<int>(block.type())
                         << ","
                         << "\"" << block.content() << "\""
                         << ","
                         << "{"
                         << "isSafe:" << (block.isSafe() ? "true" : "false")
                         << ","
                         << "expressionType:"
                         << "ExpressionType." << ExpressionTypeUtility::string(block.expressionType()) //<< static_cast<int>(block.expressionType())
                         << "}"
                         << ")";

            if (&block != &blockStream.back()) {
                blockContent << ",";
            }

            blockContent << "\n";
        }

        blockContent << "]";
        blockContent << "\n";

        return blockContent.str();
    }

    std::string exportBlockStreamToFilePath(const IrLibPlus::BlockStream& blockStream, std::string filePath)
    {
    }
};
}

#endif /* defined(__irlib_plus__BlockExporter__) */