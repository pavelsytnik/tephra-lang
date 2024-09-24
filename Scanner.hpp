#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iterator>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Token.hpp"

namespace tephra
{
class Scanner
{
private:
    std::string _source;
    std::vector<Token> _tokens;

    std::unordered_map<std::string, TokenType> _keywords {
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
        {"nil",      TokenType::Nil},
    };

    std::string::const_iterator _currentPos  = _source.cbegin();
    std::string::const_iterator _sourceEnd   = _source.cend();
    std::string::const_iterator _lexemeBegin = _currentPos;

    unsigned _line = 1;
    unsigned _char = 1;

public:
    Scanner(std::string&& source) :
        _source(std::move(source))
    {}

    const std::vector<Token>& scanTokens();

private:
    inline bool hasNext() const;
    inline char next();
    inline char peek(unsigned skip = 0) const;
    inline void addToken(TokenType type);
    inline void addToken(TokenType type, Literal&& literal);
    inline bool match(char expected);
    void scanToken();
    void scanIdentifier();
    void scanNumber();
    void scanString();
};

inline bool Scanner::hasNext() const
{
    return _currentPos < _sourceEnd;
}

inline char Scanner::next()
{
    char c = *_currentPos++;

    if (c == '\n') {
        _line++;
        _char = 1;
    } else {
        _char++;
    }

    return c;
}

inline char Scanner::peek(unsigned skip) const
{
    if (std::distance(_currentPos, _sourceEnd) > skip)
        return *std::next(_currentPos, skip);
    else
        return '\0';
}

inline void Scanner::addToken(TokenType type)
{
    addToken(type, std::monostate{});
}

inline void Scanner::addToken(TokenType type, Literal&& literal)
{
    _tokens.emplace_back(type,
                         std::string{_lexemeBegin, _currentPos},
                         std::move(literal),
                         _line,
                         _char - std::distance(_lexemeBegin, _currentPos)
    );
}

inline bool Scanner::match(char expected)
{
    if (peek() != expected)
        return false;

    next();
    return true;
}
}

#endif // !defined(SCANNER_HPP)
