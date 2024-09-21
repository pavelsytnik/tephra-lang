#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "Token.hpp"
#include "TokenType.hpp"

class Scanner
{
public:
    Scanner(std::string&& source) :
        _source(std::move(source))
    {}

    const std::vector<Token>& scanTokens()
    {
        while (hasNext()) {
            _lexemeBegin = _currentPos;
            scanToken();
        }
        _tokens.emplace_back(TokenType::EndOfFile, "");

        return _tokens;
    }

private:
    bool hasNext()
    {
        return _currentPos < _sourceEnd;
    }

    void scanToken()
    {
        switch (char c = advance(); c) {
            using enum TokenType;

            // Add token for single-character sequences
            case '(': addToken(LeftParenthesis ); break;
            case ')': addToken(RightParenthesis); break;
            case '[': addToken(LeftBracket     ); break;
            case ']': addToken(RightBracket    ); break;
            case ':': addToken(Colon           ); break;
            case ';': addToken(Semicolon       ); break;
            case ',': addToken(Comma           ); break;
            case '.': addToken(Dot             ); break;
            case '-': addToken(Minus           ); break;
            case '+': addToken(Plus            ); break;
            case '*': addToken(Asterisk        ); break;
            case '/': addToken(Slash           ); break;
        }
    }

    char advance()
    {
        return *_currentPos++;
    }

    void addToken(TokenType type)
    {
        _tokens.emplace_back(type, std::string{_lexemeBegin, _currentPos});
    }

    std::string _source;
    std::vector<Token> _tokens;

    std::string::const_iterator _currentPos  = _source.cbegin();
    std::string::const_iterator _sourceEnd   = _source.cend();
    std::string::const_iterator _lexemeBegin = _currentPos;

    unsigned _line = 1;
};

#endif // !defined(SCANNER_HPP)
