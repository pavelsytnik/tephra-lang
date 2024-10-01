#include "Parser.hpp"

#include <exception>
#include <iostream>

namespace tephra
{
using enum TokenType;

std::unique_ptr<Expr> Parser::parse()
{
    try {
        return expression();
    } catch (std::runtime_error& e) {
        std::cerr << "Parsing error: "<< e.what() << "\n";
    }
}

bool Parser::eof() const
{
    return currentPos_->type == EndOfFile;
}

bool Parser::check(TokenType type) const
{
    return peek().type == type;
}

Token& Parser::consume(TokenType type, const std::string& message)
{
    if (check(type))
        return next();

    // TODO: throw a more concrete exception
    throw std::runtime_error{message};
}

Token& Parser::next()
{
    return *currentPos_++;
}

Token& Parser::prev()
{
    return *(currentPos_ - 1);
}

const Token& Parser::peek() const
{
    return *currentPos_;
}

std::unique_ptr<Expr> Parser::expression()
{
    return equality();
}

std::unique_ptr<Expr> Parser::equality()
{
    auto expr = comparison();

    while (match(Equal, NotEqual)) {
        auto& op = prev();
        auto right = comparison();
        expr = makeExpr<BinaryExpr>(
            std::move(expr),
            std::move(op),
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::comparison()
{
    auto expr = term();

    while (match(LessThan, LessThanOrEqual,
                 GreaterThan, GreaterThanOrEqual)) {
        auto& op = prev();
        auto right = term();
        expr = makeExpr<BinaryExpr>(
            std::move(expr),
            std::move(op),
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::term()
{
    auto expr = factor();

    while (match(Minus, Plus)) {
        auto& op = prev();
        auto right = factor();
        expr = makeExpr<BinaryExpr>(
            std::move(expr),
            std::move(op),
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::factor()
{
    auto expr = unary();

    while (match(Asterisk, Slash)) {
        auto& op = prev();
        auto right = unary();
        expr = makeExpr<BinaryExpr>(
            std::move(expr),
            std::move(op),
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::unary()
{
    while (match(Minus, Plus, Not)) {
        auto& op = prev();
        auto right = unary();
        return makeExpr<UnaryExpr>(
            std::move(op),
            std::move(right)
        );
    }

    return primary();
}

std::unique_ptr<Expr> Parser::primary()
{
    if (match(Number, String))
        return makeExpr<LiteralExpr>(
            std::move(prev())
        );

    if (match(LeftParenthesis)) {
        auto expr = expression();
        consume(RightParenthesis, "`)` expected");
        return makeExpr<GroupingExpr>(
            std::move(expr)
        );
    }

    return nullptr; // TODO: implement somehow an empty expression
                    // because `nullptr` causes errors
}
}
