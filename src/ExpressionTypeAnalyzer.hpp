#include <string>
#include <map>
#import "ExpressionType.hpp"

namespace IrLibPlus {

class ExpressionTypeAnalyzer {
    static std::map<const std::string, ExpressionType> keywords;

public:
    ExpressionType detectExpressionType(std::string expression);
};
}
