#include "Prefix.h"
#include "Parser.hpp"
#include "ExpressionTypeAnalyzer.hpp"
#include <iostream>

namespace IrLibPlus
{
const std::string Parser::ExpressionStart = "{%";
const std::string Parser::ExpressionEnd = "%}";

namespace
{
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
    void print(T&& message, std::string color, bool addLineBreak = false)
    {
#if DEBUG
        const auto colorSupport = getTermSupportsColor();
        if (colorSupport) {
            std::cout << "\033[" << color;
        }
        std::cout << message;
        if (colorSupport) {
            std::cout << "\033[0;m";
        }
        if (addLineBreak) {
            std::cout << std::endl;
        }
#endif
    }

    template <typename T> void print(T&& message, bool addLineBreak = false)
    {
        print(std::forward<T>(message), "7;33m", addLineBreak);
    }
}


Block Parser::pushBlock(std::string content,
                        BlockType type,
                        ExpressionType expressionType,
                        bool isSafe,
                        int line)
{
    auto currentBlock = Block(content, type, expressionType, isSafe);

    blocks.push_back(currentBlock);
    if (line > 0) {
        print("(add block @", false);
        print(line, false);
        print(")");
    }
    return currentBlock;
}

/**
 * Analyze and categorize expressions
 */
void Parser::analyze(const TokenStream&& tokenStream)
{
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
            bool trimToken = false;

            if (firstChar == BlockStart) {
                blockStartCount++;
                trimToken = true;
            } else if (firstChar == BlockEnd) {
                // if (tokenLength == 1) {
                //     blockStartCount--;
                // }
                trimToken = true;
            }

            if (tokenLength > 1 && token[1] == ExpressionChar
                && token[tokenLength - 2] == ExpressionChar
                && token[tokenLength - 1] == BlockEnd
                && blockStartCount == 1) {
                expressionType = expressionTypeAnalyzer.detectExpressionType(
                    token.substr(2, tokenLength - 4));
                blockType = BlockType::EXPRESSION;
                trimToken = true;
            }

            if (blockStartCount == 0) {
                trimToken = false;
            }

            if (blockStartCount == BlockDelimiterRepeatNoSafe) {
                blockType = BlockType::VARIABLE;
            } else if (blockStartCount == BlockDelimiterRepeatSafe) {
                blockType = BlockType::VARIABLE;
                isSafe = true;
            } else if (blockStartCount > BlockDelimiterRepeatSafe) {
                blockStartCount--;
                pushBlock(std::string(1, BlockStart),
                          BlockType::STATIC,
                          ExpressionType::UNKNOWN,
                          false,
                          __LINE__);
                //                continue;
            }

            print("token: ");
            print(token);
            print(" bsc: ");
            print(blockStartCount);
            print("\n");
            if (trimToken && tokenLength <= 2) {
                // Skip this
                // currentBlockContent.append("");
            } else if (trimToken) {
                currentBlockContent.append(token.substr(1, tokenLength - 2));
            } else {
                currentBlockContent.append(token);
            }

            if (lastChar == BlockEnd) {
                blockStartCount--;
            }
            print(" after: ");
            print(blockStartCount);
            print("\n");

            if (blockStartCount < 0) {
                // pushBlock(
                //     // std::to_string(blockStartCount),
                //     std::string(1, BlockEnd),
                //     BlockType::STATIC,
                //     ExpressionType::UNKNOWN,
                //     false,
                //     __LINE__);

                // Reset the block start count
                blockStartCount = 0;
                continue;
            } else if (blockStartCount == 0) {
                pushBlock(currentBlockContent,
                          blockType,
                          expressionType,
                          isSafe,
                          __LINE__);

                currentBlockContent = "";
                isSafe = false;
                blockType = BlockType::STATIC;
                expressionType = ExpressionType::UNKNOWN;
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
