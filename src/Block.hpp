#ifndef __irlib_plus__Block__
#define __irlib_plus__Block__

#include <string>
#include <vector>
#include "ExpressionType.hpp"

namespace IrLibPlus {
enum class BlockType {
    STATIC,
    VARIABLE,
    REPEATING,
    EXPRESSION,
    CONDITIONAL,
};

class Block {
    std::string content_;
    std::string error_;

    BlockType type_;
    ExpressionType expressionType_;
    bool isSafe_;
    bool hasError_;

public:
    explicit Block(std::string content, BlockType type, ExpressionType expressionType, bool isSafe)
        : content_(content)
        , type_(type)
        , expressionType_(expressionType)
        , isSafe_(isSafe)
    {
        hasError_ = false;
    }

    explicit Block(std::string content, std::string error)
        : content_(content)
        , error_(error)
    {
        hasError_ = true;
        isSafe_ = false;
        type_ = BlockType::STATIC;
        expressionType_ = ExpressionType::UNKNOWN;
    }

    const std::string& content() const
    {
        return content_;
    }

    BlockType type() const noexcept
    {
        return type_;
    }

    ExpressionType expressionType() const noexcept
    {
        return expressionType_;
    }

    bool isSafe() const noexcept
    {
        return isSafe_;
    }

    bool hasError() const noexcept
    {
        return hasError_;
    }
};

//using BlockStream = std::vector<Block>;
typedef std::vector<Block> BlockStream;

class BlockTypeUtility {
public:
    const static std::string string(BlockType type)
    {
        switch (type) {
        case BlockType::STATIC:
            return "STATIC";
            break;
        case BlockType::VARIABLE:
            return "VARIABLE";
            break;
        case BlockType::REPEATING:
            return "REPEATING";
            break;
        case BlockType::EXPRESSION:
            return "EXPRESSION";
            break;
        case BlockType::CONDITIONAL:
            return "CONDITIONAL";
            break;

        default:
            return "Error - unknown type";
        }
    }
};
}

#endif /* defined(__irlib_plus__Block__) */
