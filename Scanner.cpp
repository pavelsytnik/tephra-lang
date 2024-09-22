#include "Scanner.hpp"

namespace tephra
{
const std::vector<Token>& Scanner::scanTokens()
{
    while (hasNext()) {
        _lexemeBegin = _currentPos;
        scanToken();
    }
    _tokens.emplace_back(TokenType::EndOfFile, "");

    return _tokens;
}

void Scanner::scanToken()
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
}
