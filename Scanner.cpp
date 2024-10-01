#include "Scanner.hpp"

#include <cctype>

#include "Tephra.hpp"

namespace tephra
{
std::vector<Token>& Scanner::scanTokens()
{
    while (hasNext()) {
        lexemeBegin_ = currentPos_;
        scanToken();
    }

    lexemeBegin_ = sourceEnd_;
    makeToken(TokenType::EndOfFile);

    return tokens_;
}

void Scanner::scanToken()
{
    switch (char c = next(); c) {
    using enum TokenType;

    case '(': makeToken(LeftParenthesis ); break;
    case ')': makeToken(RightParenthesis); break;
    case '[': makeToken(LeftBracket     ); break;
    case ']': makeToken(RightBracket    ); break;
    case '{': makeToken(LeftBrace       ); break;
    case '}': makeToken(RightBrace      ); break;
    case ':': makeToken(Colon           ); break;
    case ';': makeToken(Semicolon       ); break;
    case ',': makeToken(Comma           ); break;
    case '.': makeToken(Dot             ); break;
    case '~': makeToken(BitwiseNot      ); break;
    
    case '-':
        makeToken(match('=') ? MinusAssignment : Minus);
        break;
    case '+':
        makeToken(match('=') ? PlusAssignment : Plus);
        break;
    case '*':
        makeToken(match('=') ? AsteriskAssignment : Asterisk);
        break;
    case '&':
        makeToken(match('=') ? BitwiseAndAssignment : BitwiseAnd);
        break;
    case '|':
        makeToken(match('=') ? BitwiseOrAssignment : BitwiseOr);
        break;
    case '^':
        makeToken(match('=') ? BitwiseXorAssignment : BitwiseXor);
        break;

    case '<':
        makeToken(match('=') ? LessThanOrEqual : LessThan);
        break;
    case '>':
        makeToken(match('=') ? GreaterThanOrEqual : GreaterThan);
        break;

    case '=':
        if (match('='))
            makeToken(Equal);
        else if (match('>'))
            makeToken(Arrow);
        else
            makeToken(Assignment);
        break;

    case '/':
        if (match('/'))
            while (hasNext() && peek() != '\n')
                next();
        else
            makeToken(match('=') ? SlashAssignment : Slash);
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
            makeToken(NotEqual);
        else
            tephra::error(line_, char_ - 1,
                          "unexpected character `" + std::string{c} + "`");
        break;
    }
}

void Scanner::scanIdentifier()
{
    while (std::isalnum(peek()))
        next();

    if (std::string lexeme(lexemeBegin_, currentPos_);
        keywords_.contains(lexeme)
    )
        makeToken(keywords_[lexeme]);
    else
        makeToken(TokenType::Identifier);
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

    makeNumber();
}

void Scanner::scanString()
{
    while (peek() != '"') {
        if (char c = peek();  c == '\r' || c == '\n' || c == '\0') {
            tephra::error(line_, char_,
                          "closing `\"` in string literal expected");
            return;
        }

        next();
    }

    next(); // Consume closing `"`
    makeString();
}

bool Scanner::hasNext() const
{
    return currentPos_ < sourceEnd_;
}

char Scanner::next()
{
    char c = *currentPos_++;

    if (c == '\n') {
        line_++;
        char_ = 1;
    } else {
        char_++;
    }

    return c;
}

char Scanner::peek(unsigned skip) const
{
    if (std::distance(currentPos_, sourceEnd_) > skip)
        return *std::next(currentPos_, skip);
    else
        return '\0';
}

bool Scanner::match(char expected)
{
    if (peek() != expected)
        return false;

    next();
    return true;
}

void Scanner::makeToken(TokenType type, Literal&& literal)
{
    tokens_.emplace_back(
        type,
        std::string{lexemeBegin_, currentPos_},
        std::move(literal),
        line_,
        char_ - std::distance(lexemeBegin_, currentPos_)
    );
}

void Scanner::makeToken(TokenType type)
{
    makeToken(type, std::monostate{});
}

void Scanner::makeNumber()
{
    makeToken(
        TokenType::Number,
        std::stod(std::string{lexemeBegin_, currentPos_})
    );
}

void Scanner::makeString()
{
    makeToken(
        TokenType::String,
        std::string{std::next(lexemeBegin_), std::prev(currentPos_)}
    );
}
}
