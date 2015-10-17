#include <string>
#include <vector>

namespace IrLibPlus {
using Token = std::string;
using TokenStream = std::vector<Token>;

class Tokenizer {
public:
    TokenStream tokenize(const std::string& input);
};
}
