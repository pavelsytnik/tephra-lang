#ifndef TEPHRA_HPP
#define TEPHRA_HPP

#include <string>

namespace tephra
{
void run(std::string&& source);
void runFile(const std::string& path);
void runPrompt();
}

#endif // !defined(TEPHRA_HPP)
