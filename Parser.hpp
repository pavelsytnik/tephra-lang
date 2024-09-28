#ifndef TEPHRA_PARSER_HPP
#define TEPHRA_PARSER_HPP

#include <initializer_list>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>

#include "Expr.hpp"
#include "Token.hpp"

namespace tephra
{
class Parser {
private:
    std::vector<Token> _tokens;
    std::vector<Token>::iterator _currentPos = _tokens.begin();

public:
    Parser(std::vector<Token>&& tokens)
    :
        _tokens{std::move(tokens)}
    {}

    std::unique_ptr<Expr> parse();

private:
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type) const;
    Token& consume(TokenType type, const std::string& message);

    bool eof() const;
    Token& next();
    Token& prev();
    const Token& peek() const;
};
}

#endif // !defined(TEPHRA_PARSER_HPP)
