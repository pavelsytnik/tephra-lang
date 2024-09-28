#include "Scanner.hpp"

#include <cctype>

#include "Tephra.hpp"

namespace tephra
{
const std::vector<Token>& Scanner::scanTokens()
{
    while (hasNext()) {
        _lexemeBegin = _currentPos;
        scanToken();
    }

    _lexemeBegin = _sourceEnd;
    addToken(TokenType::EndOfFile);

    return _tokens;
}

void Scanner::scanToken()
{
    switch (char c = next(); c) {
    using enum TokenType;

    case '(': addToken(LeftParenthesis ); break;
    case ')': addToken(RightParenthesis); break;
    case '[': addToken(LeftBracket     ); break;
    case ']': addToken(RightBracket    ); break;
    case '{': addToken(LeftBrace       ); break;
    case '}': addToken(RightBrace      ); break;
    case ':': addToken(Colon           ); break;
    case ';': addToken(Semicolon       ); break;
    case ',': addToken(Comma           ); break;
    case '.': addToken(Dot             ); break;
    case '~': addToken(BitwiseNot      ); break;
    
    case '-':
        addToken(match('=') ? MinusAssignment : Minus);
        break;
    case '+':
        addToken(match('=') ? PlusAssignment : Plus);
        break;
    case '*':
        addToken(match('=') ? AsteriskAssignment : Asterisk);
        break;
    case '&':
        addToken(match('=') ? BitwiseAndAssignment : BitwiseAnd);
        break;
    case '|':
        addToken(match('=') ? BitwiseOrAssignment : BitwiseOr);
        break;
    case '^':
        addToken(match('=') ? BitwiseXorAssignment : BitwiseXor);
        break;

    case '<':
        addToken(match('=') ? LessThanOrEqual : LessThan);
        break;
    case '>':
        addToken(match('=') ? GreaterThanOrEqual : GreaterThan);
        break;

    case '=':
        if (match('='))
            addToken(Equal);
        else if (match('>'))
            addToken(Arrow);
        else
            addToken(Assignment);
        break;

    case '/':
        if (match('/'))
            while (hasNext() && peek() != '\n')
                next();
        else
            addToken(match('=') ? SlashAssignment : Slash);
        break;

    case ' ':
    case '\t':
    case '\r':
    case '\n':
        break;

    default:
        if (std::isalpha(c))
            scanIdentifier();
        else if (std::isdigit(c))
            scanNumber();
        else if (c == '"')
            scanString();
        else if (c == '!' && match('='))
            addToken(NotEqual);
        else
            tephra::error(_line, _char - 1,
                          "unexpected character `" + std::string{c} + "`");
        break;
    }
}

void Scanner::scanIdentifier()
{
    while (std::isalnum(peek()))
        next();

    if (std::string lexeme(_lexemeBegin, _currentPos);
        _keywords.contains(lexeme)
    )
        addToken(_keywords[lexeme]);
    else
        addToken(TokenType::Identifier);
}

void Scanner::scanNumber()
{
    while (std::isdigit(peek()))
        next();

    if (peek(0) == '.' && std::isdigit(peek(1))) {
        next(); // Consume `.`
        while (std::isdigit(peek()))
            next();
    }

    addToken(TokenType::Number,
             std::stod(std::string{_lexemeBegin, _currentPos}));
}

void Scanner::scanString()
{
    while (peek() != '"') {
        if (char c = peek();  c == '\r' || c == '\n' || c == '\0') {
            tephra::error(_line, _char,
                          "closing `\"` in string literal expected");
            return;
        }

        next();
    }

    next(); // Consume closing `"`
    addToken(TokenType::String,
             std::string{std::next(_lexemeBegin), std::prev(_currentPos)});
}
}
