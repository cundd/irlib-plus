#include <string>
#include <map>
#include <iostream>
#import "ExpressionTypeAnalyzer.hpp"

namespace IrLibPlus {

void trimToFirstWord(std::string& expression) {
    auto position = expression.find_first_of(" \t", 1);
    if (position != std::string::npos) {
        expression = expression.substr(0, position);
    }
}

std::map<const std::string, ExpressionType> ExpressionTypeAnalyzer::keywords = {
    { "view", ExpressionType::VIEW },
    { "for", ExpressionType::REPEATING_START },
    { "endfor", ExpressionType::REPEATING_END },
    { "if", ExpressionType::CONDITIONAL_START },
    { "endif", ExpressionType::CONDITIONAL_END },
    { "else", ExpressionType::ELSE },
};

ExpressionType ExpressionTypeAnalyzer::detectExpressionType(std::string expression)
{
    trimToFirstWord(expression);

    if (ExpressionTypeAnalyzer::keywords.find(expression) != ExpressionTypeAnalyzer::keywords.end()) {
        return ExpressionTypeAnalyzer::keywords[expression];
    }
    return ExpressionType::UNKNOWN;
}
}
