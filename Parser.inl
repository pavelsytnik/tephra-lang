namespace tephra
{
template <TokenTypeEntry... Ts>
bool Parser::match(Ts... types)
{
    bool occurred = (check(types) || ...);

    if (occurred)
        next();

    return occurred;
}
}
