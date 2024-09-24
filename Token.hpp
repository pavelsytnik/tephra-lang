#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <string>

namespace tephra
{
enum class TokenType;

struct Token
{
    const TokenType type;
    const std::string lexeme;
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

    EndOfFile,
};

std::string stringify(TokenType type);

inline std::ostream& operator<<(std::ostream& out, const TokenType& type)
{
    return out << stringify(type);
}

inline std::ostream& operator<<(std::ostream& out, const Token& token)
{
    return out << token.type << ": '" << token.lexeme << "'";
}
}

#endif // !defined(TOKEN_HPP)
