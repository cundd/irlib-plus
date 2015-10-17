#include <string>
#include <map>
#include <iostream>
#import "ExpressionTypeAnalyzer.hpp"

namespace IrLibPlus {

std::map<const std::string, ExpressionType> ExpressionTypeAnalyzer::keywords = {
    { "view", ExpressionType::VIEW },
    { "for", ExpressionType::REPEATING_START },
    { "endfor", ExpressionType::REPEATING_END },
    { "if", ExpressionType::CONDITIONAL_START },
    { "endif", ExpressionType::CONDITIONAL_END },
    { "else", ExpressionType::ELSE },
};

ExpressionType ExpressionTypeAnalyzer::detectExpressionType(const std::string& expression)
{
    if (ExpressionTypeAnalyzer::keywords.find(expression) != ExpressionTypeAnalyzer::keywords.end()) {
        return ExpressionTypeAnalyzer::keywords[expression];
    }
    return ExpressionType::UNKNOWN;
}
}
