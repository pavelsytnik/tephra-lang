#ifndef TOKEN_TYPE_HPP
#define TOKEN_TYPE_HPP

#include <iostream>
#include <string>

#define STRINGIFY_TOKEN_TYPE(name) \
    case name: return #name

enum class TokenType
{
    LeftParenthesis,
    RightParenthesis,
    LeftBracket,
    RightBracket,

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

inline std::string stringFromTokenType(TokenType type)
{
    using enum TokenType;
    switch (type) {
        STRINGIFY_TOKEN_TYPE(LeftParenthesis);
        STRINGIFY_TOKEN_TYPE(RightParenthesis);
        STRINGIFY_TOKEN_TYPE(LeftBracket);
        STRINGIFY_TOKEN_TYPE(RightBracket);
        STRINGIFY_TOKEN_TYPE(Colon);
        STRINGIFY_TOKEN_TYPE(Semicolon);
        STRINGIFY_TOKEN_TYPE(Comma);
        STRINGIFY_TOKEN_TYPE(Dot);
        STRINGIFY_TOKEN_TYPE(Minus);
        STRINGIFY_TOKEN_TYPE(Plus);
        STRINGIFY_TOKEN_TYPE(Asterisk);
        STRINGIFY_TOKEN_TYPE(Slash);
        STRINGIFY_TOKEN_TYPE(Equal);
        STRINGIFY_TOKEN_TYPE(NotEqual);
        STRINGIFY_TOKEN_TYPE(LessThan);
        STRINGIFY_TOKEN_TYPE(GreaterThan);
        STRINGIFY_TOKEN_TYPE(LessThanOrEqual);
        STRINGIFY_TOKEN_TYPE(GreaterThanOrEqual);
        STRINGIFY_TOKEN_TYPE(BitwiseNot);
        STRINGIFY_TOKEN_TYPE(BitwiseAnd);
        STRINGIFY_TOKEN_TYPE(BitwiseOr);
        STRINGIFY_TOKEN_TYPE(BitwiseXor);
        STRINGIFY_TOKEN_TYPE(Assignment);
        STRINGIFY_TOKEN_TYPE(MinusAssignment);
        STRINGIFY_TOKEN_TYPE(PlusAssignment);
        STRINGIFY_TOKEN_TYPE(AsteriskAssignment);
        STRINGIFY_TOKEN_TYPE(SlashAssignment);
        STRINGIFY_TOKEN_TYPE(BitwiseAndAssignment);
        STRINGIFY_TOKEN_TYPE(BitwiseOrAssignment);
        STRINGIFY_TOKEN_TYPE(BitwiseXorAssignment);
        STRINGIFY_TOKEN_TYPE(Arrow);
        STRINGIFY_TOKEN_TYPE(Identifier);
        STRINGIFY_TOKEN_TYPE(String);
        STRINGIFY_TOKEN_TYPE(Number);
        STRINGIFY_TOKEN_TYPE(If);
        STRINGIFY_TOKEN_TYPE(Elif);
        STRINGIFY_TOKEN_TYPE(Else);
        STRINGIFY_TOKEN_TYPE(While);
        STRINGIFY_TOKEN_TYPE(For);
        STRINGIFY_TOKEN_TYPE(In);
        STRINGIFY_TOKEN_TYPE(Fun);
        STRINGIFY_TOKEN_TYPE(Class);
        STRINGIFY_TOKEN_TYPE(Var);
        STRINGIFY_TOKEN_TYPE(Let);
        STRINGIFY_TOKEN_TYPE(Break);
        STRINGIFY_TOKEN_TYPE(Continue);
        STRINGIFY_TOKEN_TYPE(Return);
        STRINGIFY_TOKEN_TYPE(And);
        STRINGIFY_TOKEN_TYPE(Or);
        STRINGIFY_TOKEN_TYPE(Not);
        STRINGIFY_TOKEN_TYPE(True);
        STRINGIFY_TOKEN_TYPE(False);
        STRINGIFY_TOKEN_TYPE(Nil);
        STRINGIFY_TOKEN_TYPE(EndOfFile);
    }
    return "UnknownToken";
}

inline std::ostream& operator<<(std::ostream& out, const TokenType& type)
{
    return out << stringFromTokenType(type);
}

#undef STRINGIFY_TOKEN_TYPE

#endif // !defined(TOKEN_TYPE_HPP)
