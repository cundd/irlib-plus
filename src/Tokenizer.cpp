#include <string>

#include <iostream>
#include "Tokenizer.hpp"
#include "Parser.hpp"

namespace IrLibPlus {

template <typename T>
class TD;

TokenStream Tokenizer::tokenize(const std::string& input)
{
    // std::cout
    //     << IrLibPlus::Parser::ExpressionStart << "\n"
    //     << IrLibPlus::Parser::ExpressionEnd << "\n"
    //     << IrLibPlus::Parser::BlockStart << "\n"
    //     << IrLibPlus::Parser::BlockEnd << "\n"
    //     << std::endl;

    Token currentToken = "";
    TokenStream tokenStream = {};
    bool inBlock = false;
    bool inTag = false;

    for (int i = 0; i < input.length(); i++) {
        const char currentCharacter = input[i];

        if (currentCharacter == IrLibPlus::Parser::BlockStart) {
            inBlock = true;
        }
        if (currentCharacter == IrLibPlus::Parser::TagStart) {
            inTag = true;
        }

        if (currentCharacter != IrLibPlus::Parser::BlockStart
            && currentCharacter != IrLibPlus::Parser::TagStart) {
            currentToken.append(1, currentCharacter);
        }

        if (currentCharacter == IrLibPlus::Parser::BlockStart
            || currentCharacter == IrLibPlus::Parser::BlockEnd
            || currentCharacter == IrLibPlus::Parser::TagStart
            || currentCharacter == IrLibPlus::Parser::TagEnd) {
            tokenStream.push_back(currentToken);
            currentToken = "";
        }

        if (currentCharacter == IrLibPlus::Parser::BlockStart
            || currentCharacter == IrLibPlus::Parser::TagStart) {
            currentToken.append(1, currentCharacter);
        }

        if (currentCharacter == IrLibPlus::Parser::BlockEnd) {
            inBlock = false;
        }
        if (currentCharacter == IrLibPlus::Parser::TagEnd) {
            inTag = false;
        }

        // switch (currentCharacter) {
        // case IrLibPlus::Parser::BlockStart:
        //     tokenStream.push_back(currentToken);
        //     currentToken = "";
        //     std::cout << "+";
        //     break;
        //
        // case IrLibPlus::Parser::BlockEnd:
        //     tokenStream.push_back(currentToken);
        //     currentToken = "";
        //     std::cout << "-";
        //     break;
        //
        // default:
        //     currentToken.append(1, currentCharacter);
        //     break;
        // }
    }

    tokenStream.push_back(currentToken);
    return tokenStream;
};
}
