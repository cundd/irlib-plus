//
//
// Parser
#include <iomanip>
#include <vector>
#include "Block.hpp"
#import "Tokenizer.hpp"
#import "ParserException.hpp"

namespace IrLibPlus {

class Parser {
    /**
     * List of blocks
     */
    IrLibPlus::BlockStream blocks;

    /**
     * Tokenizer to split the input string into tokens
     */
    Tokenizer tokenizer;

    /**
     * Defines if the parser should throw exceptions on errors
     */
    bool strict = false;

    void analyze(const TokenStream&& tokenStream);

public:
    /**
     * Start of an expression
     */
    static const std::string ExpressionStart;

    /**
     * End of an expression
     */
    static const std::string ExpressionEnd;

    /**
     * Start character of a block
     */
    static constexpr char BlockStart = '{';

    /**
     * End character of a block
     */
    static constexpr char BlockEnd = '}';

    /**
     * Start character of a tag
     */
    static constexpr char TagStart = '<';

    /**
     * End character of a tag
     */
    static constexpr char TagEnd = '>';

    /**
     * Character for an expression
     */
    static constexpr char ExpressionChar = '%';

    /**
     * Number the block start and end characters have to occur to build an un-safe block
     */
    static constexpr int BlockDelimiterRepeatNoSafe = 2;

    /**
     * Number the block start and end characters have to occur to build an safe block
     */
    static constexpr int BlockDelimiterRepeatSafe = 3;

    IrLibPlus::BlockStream& parse(const std::string& input)
    {
        analyze(tokenizer.tokenize(input));
        return blocks;
    }
};
}
