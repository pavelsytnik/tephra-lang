#ifndef TEPHRA_EXPR_PRINTER_HPP
#define TEPHRA_EXPR_PRINTER_HPP

#include <string>

#include "Expr.hpp"

namespace tephra
{
struct ExprPrinter
{
    std::string operator()(const BinaryExpr& expr) const
    {
        std::string result;
        result += "(";
        result += expr.op.lexeme;
        result += " ";
        result += std::visit(*this, *expr.left);
        result += " ";
        result += std::visit(*this, *expr.right);
        result += ")";

        return result;
    }

    std::string operator()(const GroupingExpr& expr) const
    {
        std::string result;
        result += "(group ";
        result += std::visit(*this, *expr.expr);
        result += ")";

        return result;
    }

    std::string operator()(const LiteralExpr& expr) const
    {
        if (const auto& lit = expr.literal;
            std::holds_alternative<double>(lit))
            return std::to_string(std::get<double>(lit));
        else if (std::holds_alternative<std::string>(lit))
            return std::get<std::string>(lit);
        else
            return "nil";
    }

    std::string operator()(const UnaryExpr& expr) const
    {
        std::string result;
        result += "(";
        result += expr.op.lexeme;
        result += " ";
        result += std::visit(*this, *expr.right);
        result += ")";

        return result;
    }
};
}

#endif // !defined(TEPHRA_EXPR_PRINTER_HPP)
