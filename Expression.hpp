#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <memory>
#include <utility>

#include "Token.hpp"

namespace tephra
{
class Expression
{
public:
    virtual ~Expression() = 0;
};

class BinaryExpression : public Expression
{
public:
    BinaryExpression(std::unique_ptr<Expression> left,
                     Token&& op,
                     std::unique_ptr<Expression> right
    ) :
        left(std::move(left)),
        op(std::move(op)),
        right(std::move(right))
    {}

    const std::unique_ptr<Expression> left;
    const Token op;
    const std::unique_ptr<Expression> right;
};

class GroupingExpression : public Expression
{
public:
    GroupingExpression(std::unique_ptr<Expression> expr
    ) :
        expr(std::move(expr))
    {}

    const std::unique_ptr<Expression> expr;
};

class LiteralExpression : public Expression
{
public:
    LiteralExpression(Literal&& literal
    ) :
        literal(std::move(literal))
    {}

    const Literal literal;
};

class UnaryExpression : public Expression
{
public:
    UnaryExpression(Token&& op,
                    std::unique_ptr<Expression> expr
    ) :
        op(std::move(op)),
        expr(std::move(expr))
    {}

    const Token op;
    const std::unique_ptr<Expression> expr;
};

inline Expression::~Expression() {}
}

#endif // !defined(EXPRESSION_HPP)
