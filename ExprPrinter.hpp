#ifndef TEPHRA_EXPR_PRINTER_HPP
#define TEPHRA_EXPR_PRINTER_HPP

#include <format>
#include <string>

#include "Expr.hpp"

namespace tephra
{
struct ExprPrinter
{
    std::string operator()(const BinaryExpr& expr) const
    {
        auto left  = std::visit(*this, *expr.left);
        auto op    = expr.op.lexeme;
        auto right = std::visit(*this, *expr.right);

        return std::format("({1} {0} {2})", left, op, right);
    }

    std::string operator()(const GroupingExpr& expr) const
    {
        auto content = std::visit(*this, *expr.expr);

        return std::format("(`group` {0})", content);
    }

    std::string operator()(const LiteralExpr& expr) const
    {
        return expr.literal.lexeme;
    }

    std::string operator()(const UnaryExpr& expr) const
    {
        auto op    = expr.op.lexeme;
        auto right = std::visit(*this, *expr.right);

        return std::format("({0} {1})", op, right);
    }

    template <typename T>
    std::string operator()(const T&) const
    {
        static_assert(
            alwaysFalse_<T>,
            "tephra::ExprPrinter is not exhaustive"
        );
    }

private:
    template <typename>
    static constexpr bool alwaysFalse_ = false;
};
}

#endif // !defined(TEPHRA_EXPR_PRINTER_HPP)
