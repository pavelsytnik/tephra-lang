#ifndef TEPHRA_TOKEN_HPP
#define TEPHRA_TOKEN_HPP

#include <concepts>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <variant>

namespace tephra
{
enum class TokenType;

template <typename T>
concept TokenTypeEntry = std::same_as<T, TokenType>;

using Literal = std::variant
<
    std::monostate,
    std::string,
    double,
    bool,
    std::nullptr_t
>;

struct Token
{
    TokenType type;
    std::string lexeme;
    Literal literal;
    unsigned line;
    unsigned column;

    Token(TokenType type,
          std::string&& lexeme,
          Literal&& literal,
          unsigned line,
          unsigned column)
    :
        type{type},
        lexeme{std::move(lexeme)},
        literal{std::move(literal)},
        line{line},
        column{column}
    {}
};

enum class TokenType
{
    LeftParenthesis,
    RightParenthesis,
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,

    Colon,
    Semicolon,
    Comma,
    Dot,

    Minus,
    Plus,
    Asterisk,
    Slash,

    Equal,
    NotEqual,
    LessThan,
    GreaterThan,
    LessThanOrEqual,
    GreaterThanOrEqual,

    BitwiseNot,
    BitwiseAnd,
    BitwiseOr,
    BitwiseXor,

    Assignment,
    MinusAssignment,
    PlusAssignment,
    AsteriskAssignment,
    SlashAssignment,
    BitwiseAndAssignment,
    BitwiseOrAssignment,
    BitwiseXorAssignment,

    Arrow,

    Identifier,
    String,
    Number,

    If,
    Elif,
    Else,
    While,
    For,
    In,
    Fun,
    Class,
    Var,
    Let,
    Break,
    Continue,
    Return,
    And,
    Or,
    Not,
    True,
    False,
    Nil,

    EndOfFile
};

std::string stringify(TokenType type);

inline std::ostream& operator<<(std::ostream& out, const TokenType& type)
{
    return out << stringify(type);
}

inline std::ostream& operator<<(std::ostream& out, const Token& token)
{
    return out << "[" << token.line << ":" << token.column << "] "
               << token.type << ": '" << token.lexeme << "'";
}
}

#endif // !defined(TEPHRA_TOKEN_HPP)
