#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "TokenType.hpp"

struct Token
{
    const TokenType type;
    const std::string lexeme;
};

#endif // !defined(TOKEN_HPP)
