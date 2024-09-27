#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <memory>
#include <utility>
#include <variant>

#include "Token.hpp"

namespace tephra
{
struct BinaryExpr;
struct GroupingExpr;
struct LiteralExpr;
struct UnaryExpr;

using Expr = std::variant<
    BinaryExpr,
    GroupingExpr,
    LiteralExpr,
    UnaryExpr
>;

struct BinaryExpr {
    const std::unique_ptr<Expr> left;
    const Token op;
    const std::unique_ptr<Expr> right;

    BinaryExpr(std::unique_ptr<Expr> left,
               Token&& op,
               std::unique_ptr<Expr> right)
    :
        left{std::move(left)},
        op{std::move(op)},
        right{std::move(right)}
    {}
};

struct GroupingExpr {
    const std::unique_ptr<Expr> expr;

    GroupingExpr(std::unique_ptr<Expr> expr)
    :
        expr{std::move(expr)}
    {}
};

struct LiteralExpr {
    const Literal literal;

    LiteralExpr(Literal&& literal)
    :
        literal{std::move(literal)}
    {}
};

struct UnaryExpr {
    const Token op;
    const std::unique_ptr<Expr> right;

    UnaryExpr(Token&& op,
              std::unique_ptr<Expr> right)
    :
        op{std::move(op)},
        right{std::move(right)}
    {}
};
}

#endif // !defined(EXPRESSION_HPP)
