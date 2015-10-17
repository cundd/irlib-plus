#include "Parser.hpp"
#include "ExpressionTypeAnalyzer.hpp"
#include <iostream>

namespace IrLibPlus {
const std::string Parser::ExpressionStart = "{%";
const std::string Parser::ExpressionEnd = "%}";

namespace {
    bool getTermSupportsColor()
    {

        auto termRaw = std::getenv("TERM");
        if (termRaw == nullptr) {
            return false;
        }
        auto term = std::string(termRaw);
        if (term == "xterm-256color") {
            return true;
        }
        return false;
    };

    template <typename T>
    void print(T&& message, std::string color = "7;33m")
    {
        const auto colorSupport = getTermSupportsColor();
        if (colorSupport) {
            std::cout << " \033[" << color;
        }
        std::cout << message;
        if (colorSupport) {
            std::cout << "\033[0;m";
        }
        std::cout << std::endl;
    }
}

void Parser::analyze(const TokenStream&& tokenStream)
{
    /**
	 * Analyze and categorize expressions
	 */
    ExpressionTypeAnalyzer expressionTypeAnalyzer;

    int size = tokenStream.size();

    bool isSafe = false;
    int blockStartCount = 0;
    BlockType blockType = BlockType::STATIC;
    ExpressionType expressionType = ExpressionType::UNKNOWN;
    std::string currentBlockContent;

    for (int i = 0; i < size; i++) {
        auto token = tokenStream[i];
        auto tokenLength = token.length();
        Token nextToken;

        if (i + 1 < size) {
            nextToken = tokenStream[i + 1];
        }

        if (tokenLength >= 1) {
            char firstChar = token[0];
            char lastChar = token[tokenLength - 1];

            if (firstChar == BlockStart) {
                blockStartCount++;
            }
            if (tokenLength > 1
                && token[1] == ExpressionChar
                && token[tokenLength - 2] == ExpressionChar
                && token[tokenLength - 1] == BlockEnd
                && blockStartCount == 1) {
                expressionType = expressionTypeAnalyzer.detectExpressionType(token.substr(2, tokenLength - 4));
                blockType = BlockType::EXPRESSION;
            }

            currentBlockContent.append(token);

            if (blockStartCount == BlockDelimiterRepeatNoSafe) {
                blockType = BlockType::VARIABLE;
            }
            if (blockStartCount == BlockDelimiterRepeatSafe) {
                blockType = BlockType::VARIABLE;
                isSafe = true;
            }

            if (lastChar == BlockEnd) {
                blockStartCount--;
            }

            // if (token[0] == BlockStart
            //     && nextToken.length() > 0 && nextToken[0] == BlockStart) {
            //     std::cout << "BlockStart ";
            // }

            //            std::cout << "blockStartCount: " << blockStartCount;
            //            std::cout << std::setw(6);
            //            std::cout << "BT: " << static_cast<int>(blockType) << " ";
            //
            //            if (blockStartCount <= 0 && isSafe) {
            //                std::cout << std::setw(5);
            //                std::cout << ">sn";
            //            }
            //            else if (blockStartCount <= 0) {
            //                std::cout << std::setw(5);
            //                std::cout << "> n";
            //            }
            //            else {
            //                std::cout << std::setw(5) << " ";
            //            }
            //
            //            print(currentBlockContent);

            if (blockStartCount <= 0) {
                auto currentBlock = Block(currentBlockContent, blockType, expressionType, isSafe);
                //Block currentBlock = { currentBlockContent, blockType, expressionType, isSafe };

                currentBlockContent = "";
                isSafe = false;
                blockType = BlockType::STATIC;
                expressionType = ExpressionType::UNKNOWN;

                blocks.push_back(currentBlock);
            }
        }
    }

    if (currentBlockContent.length() > 0) {
        const std::string errorMessage = "Unmatched opening brace";
        if (strict) {
            throw ParserException(errorMessage);
        }
        auto currentBlock = Block(currentBlockContent, errorMessage);
        blocks.push_back(currentBlock);
    }
}
}
