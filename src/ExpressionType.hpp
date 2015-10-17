namespace IrLibPlus {
enum class ExpressionType {
    UNKNOWN = 0,
    VIEW,
    REPEATING_START,
    REPEATING_END,
    CONDITIONAL_START,
    CONDITIONAL_END,
    ELSE,
};

class ExpressionTypeUtility {
public:
    const static std::string string(ExpressionType type)
    {
        switch (type) {

        case ExpressionType::UNKNOWN:
            return "UNKNOWN";

        case ExpressionType::VIEW:
            return "VIEW";

        case ExpressionType::REPEATING_START:
            return "REPEATING_START";

        case ExpressionType::REPEATING_END:
            return "REPEATING_END";

        case ExpressionType::CONDITIONAL_START:
            return "CONDITIONAL_START";

        case ExpressionType::CONDITIONAL_END:
            return "CONDITIONAL_END";

        case ExpressionType::ELSE:
            return "ELSE";

        default:
            return "Error - unknown type";
        }
    }
};
}
