#ifndef TEPHRA_PARSER_HPP
#define TEPHRA_PARSER_HPP

#include <memory>
#include <utility>
#include <vector>

#include "Expr.hpp"
#include "Token.hpp"

namespace tephra
{
class Parser {
private:
    std::vector<Token> tokens_;
    std::vector<Token>::iterator currentPos_ = tokens_.begin();

public:
    Parser(std::vector<Token>&& tokens)
    :
        tokens_{std::move(tokens)}
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

    template <TokenTypeEntry... Ts>
    bool match(Ts... types);

    bool eof() const;
    bool check(TokenType type) const;

    Token& consume(TokenType type, const std::string& message);

    Token& next();
    Token& prev();
    const Token& peek() const;
};
}

#include "Parser.inl"

#endif // !defined(TEPHRA_PARSER_HPP)
