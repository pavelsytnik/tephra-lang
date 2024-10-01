#ifndef TEPHRA_SCANNER_HPP
#define TEPHRA_SCANNER_HPP

#include <iterator>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Token.hpp"

namespace tephra
{
class Scanner {
private:
    std::string source_;
    std::vector<Token> tokens_;

    std::unordered_map<std::string, TokenType> keywords_ {
        {"if",       TokenType::If},
        {"elif",     TokenType::Elif},
        {"else",     TokenType::Else},
        {"while",    TokenType::While},
        {"for",      TokenType::For},
        {"in",       TokenType::In},
        {"fun",      TokenType::Fun},
        {"class",    TokenType::Class},
        {"var",      TokenType::Var},
        {"let",      TokenType::Let},
        {"break",    TokenType::Break},
        {"continue", TokenType::Continue},
        {"return",   TokenType::Return},
        {"and",      TokenType::And},
        {"or",       TokenType::Or},
        {"not",      TokenType::Not},
        {"true",     TokenType::True},
        {"false",    TokenType::False},
        {"nil",      TokenType::Nil}
    };

    std::string::const_iterator currentPos_  = source_.cbegin();
    std::string::const_iterator sourceEnd_   = source_.cend();
    std::string::const_iterator lexemeBegin_ = currentPos_;

    unsigned line_ = 1;
    unsigned char_ = 1;

public:
    Scanner(std::string&& source) :
        source_{std::move(source)}
    {}

    std::vector<Token>& scanTokens();

private:
    bool hasNext() const;
    char next();
    char peek(unsigned skip = 0) const;

    bool match(char expected);

    void makeToken(TokenType type, Literal&& literal);
    void makeToken(TokenType type);
    void makeNumber();
    void makeString();

    void scanToken();
    void scanIdentifier();
    void scanNumber();
    void scanString();
};
}

#endif // !defined(TEPHRA_SCANNER_HPP)
