#ifndef TOKEN_TYPE_HPP
#define TOKEN_TYPE_HPP

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

#endif // !defined(TOKEN_TYPE_HPP)
