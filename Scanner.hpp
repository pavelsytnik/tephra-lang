#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iterator>
#include <string>
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

    std::string::const_iterator _currentPos  = _source.cbegin();
    std::string::const_iterator _sourceEnd   = _source.cend();
    std::string::const_iterator _lexemeBegin = _currentPos;

    unsigned _line = 1;
    unsigned _char = 0;

public:
    Scanner(std::string&& source) :
        _source(std::move(source))
    {}

    const std::vector<Token>& scanTokens();

private:
    inline bool hasNext() const;
    inline char next();
    inline char peek(std::string::difference_type skip = 0) const;
    inline void addToken(TokenType type);
    void scanToken();
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
        _char = 0;
    } else {
        _char++;
    }

    return c;
}

inline char Scanner::peek(std::string::difference_type skip) const
{
    if (std::distance(_currentPos, _sourceEnd) > skip)
        return *std::next(_currentPos, skip);
    else
        return '\0';
}

inline void Scanner::addToken(TokenType type)
{
    _tokens.emplace_back(type, std::string{_lexemeBegin, _currentPos});
}
}

#endif // !defined(SCANNER_HPP)
