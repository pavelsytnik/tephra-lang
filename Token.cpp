#include "Token.hpp"

#define CASE_TOKEN_TYPE_STRINGIFY(name) \
    case name: return #name;

std::string tephra::stringify(TokenType type)
{
    using enum TokenType;
    switch (type) {
    CASE_TOKEN_TYPE_STRINGIFY(LeftParenthesis)
    CASE_TOKEN_TYPE_STRINGIFY(RightParenthesis)
    CASE_TOKEN_TYPE_STRINGIFY(LeftBracket)
    CASE_TOKEN_TYPE_STRINGIFY(RightBracket)
    CASE_TOKEN_TYPE_STRINGIFY(LeftBrace)
    CASE_TOKEN_TYPE_STRINGIFY(RightBrace)
    CASE_TOKEN_TYPE_STRINGIFY(Colon)
    CASE_TOKEN_TYPE_STRINGIFY(Semicolon)
    CASE_TOKEN_TYPE_STRINGIFY(Comma)
    CASE_TOKEN_TYPE_STRINGIFY(Dot)
    CASE_TOKEN_TYPE_STRINGIFY(Minus)
    CASE_TOKEN_TYPE_STRINGIFY(Plus)
    CASE_TOKEN_TYPE_STRINGIFY(Asterisk)
    CASE_TOKEN_TYPE_STRINGIFY(Slash)
    CASE_TOKEN_TYPE_STRINGIFY(Equal)
    CASE_TOKEN_TYPE_STRINGIFY(NotEqual)
    CASE_TOKEN_TYPE_STRINGIFY(LessThan)
    CASE_TOKEN_TYPE_STRINGIFY(GreaterThan)
    CASE_TOKEN_TYPE_STRINGIFY(LessThanOrEqual)
    CASE_TOKEN_TYPE_STRINGIFY(GreaterThanOrEqual)
    CASE_TOKEN_TYPE_STRINGIFY(BitwiseNot)
    CASE_TOKEN_TYPE_STRINGIFY(BitwiseAnd)
    CASE_TOKEN_TYPE_STRINGIFY(BitwiseOr)
    CASE_TOKEN_TYPE_STRINGIFY(BitwiseXor)
    CASE_TOKEN_TYPE_STRINGIFY(Assignment)
    CASE_TOKEN_TYPE_STRINGIFY(MinusAssignment)
    CASE_TOKEN_TYPE_STRINGIFY(PlusAssignment)
    CASE_TOKEN_TYPE_STRINGIFY(AsteriskAssignment)
    CASE_TOKEN_TYPE_STRINGIFY(SlashAssignment)
    CASE_TOKEN_TYPE_STRINGIFY(BitwiseAndAssignment)
    CASE_TOKEN_TYPE_STRINGIFY(BitwiseOrAssignment)
    CASE_TOKEN_TYPE_STRINGIFY(BitwiseXorAssignment)
    CASE_TOKEN_TYPE_STRINGIFY(Arrow)
    CASE_TOKEN_TYPE_STRINGIFY(Identifier)
    CASE_TOKEN_TYPE_STRINGIFY(String)
    CASE_TOKEN_TYPE_STRINGIFY(Number)
    CASE_TOKEN_TYPE_STRINGIFY(If)
    CASE_TOKEN_TYPE_STRINGIFY(Elif)
    CASE_TOKEN_TYPE_STRINGIFY(Else)
    CASE_TOKEN_TYPE_STRINGIFY(While)
    CASE_TOKEN_TYPE_STRINGIFY(For)
    CASE_TOKEN_TYPE_STRINGIFY(In)
    CASE_TOKEN_TYPE_STRINGIFY(Fun)
    CASE_TOKEN_TYPE_STRINGIFY(Class)
    CASE_TOKEN_TYPE_STRINGIFY(Var)
    CASE_TOKEN_TYPE_STRINGIFY(Let)
    CASE_TOKEN_TYPE_STRINGIFY(Break)
    CASE_TOKEN_TYPE_STRINGIFY(Continue)
    CASE_TOKEN_TYPE_STRINGIFY(Return)
    CASE_TOKEN_TYPE_STRINGIFY(And)
    CASE_TOKEN_TYPE_STRINGIFY(Or)
    CASE_TOKEN_TYPE_STRINGIFY(Not)
    CASE_TOKEN_TYPE_STRINGIFY(True)
    CASE_TOKEN_TYPE_STRINGIFY(False)
    CASE_TOKEN_TYPE_STRINGIFY(Nil)
    CASE_TOKEN_TYPE_STRINGIFY(EndOfFile)
    }
    return "UnknownToken";
}
