#ifndef SCANNER_HPP
#define SCANNER_HPP

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

public:
    Scanner(std::string&& source) :
        _source(std::move(source))
    {}

    const std::vector<Token>& scanTokens();

private:
    inline bool hasNext() const;
    inline char advance();
    inline void addToken(TokenType type);
    void scanToken();
};

inline bool Scanner::hasNext() const
{
    return _currentPos < _sourceEnd;
}

inline char Scanner::advance()
{
    return *_currentPos++;
}

inline void Scanner::addToken(TokenType type)
{
    _tokens.emplace_back(type, std::string{_lexemeBegin, _currentPos});
}
}

#endif // !defined(SCANNER_HPP)
