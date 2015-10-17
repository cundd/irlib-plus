#import <exception>

namespace IrLibPlus {

class ParserException : std::exception {

public:
    explicit ParserException(const std::string& message)
        : message(message)
    {
    }
    std::string message;
};
}
