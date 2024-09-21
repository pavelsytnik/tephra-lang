#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <string>

#include "TokenType.hpp"

struct Token
{
    const TokenType type;
    const std::string lexeme;
};

inline std::ostream& operator<<(std::ostream& out, const Token& token)
{
    out << token.type << ": '" << token.lexeme << "'";
    return out;
}

#endif // !defined(TOKEN_HPP)
