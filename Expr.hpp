#ifndef TEPHRA_EXPR_HPP
#define TEPHRA_EXPR_HPP

#include <memory>
#include <utility>
#include <variant>

#include "Token.hpp"
#include "VariantTraits.hpp"

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

struct BinaryExpr
{
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    BinaryExpr(std::unique_ptr<Expr> left,
               Token&& op,
               std::unique_ptr<Expr> right)
    :
        left{std::move(left)},
        op{std::move(op)},
        right{std::move(right)}
    {}
};

struct GroupingExpr
{
    std::unique_ptr<Expr> expr;

    GroupingExpr(std::unique_ptr<Expr> expr)
    :
        expr{std::move(expr)}
    {}
};

struct LiteralExpr
{
    Literal literal;

    LiteralExpr(Literal&& literal)
    :
        literal{std::move(literal)}
    {}
};

struct UnaryExpr
{
    Token op;
    std::unique_ptr<Expr> right;

    UnaryExpr(Token&& op,
              std::unique_ptr<Expr> right)
    :
        op{std::move(op)},
        right{std::move(right)}
    {}
};

template <VariantAlternative<Expr> T, typename... Args>
std::unique_ptr<Expr> makeExpr(Args&&... args)
{
    return std::make_unique<Expr>(T{std::forward<Args>(args)...});
}
}

#endif // !defined(TEPHRA_EXPR_HPP)
