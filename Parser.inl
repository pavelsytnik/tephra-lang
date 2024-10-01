namespace tephra
{
template <std::same_as<TokenType>... Ts>
bool Parser::match(Ts... types)
{
    bool occurred = (check(types) || ...);

    if (occurred)
        next();

    return occurred;
}
}
