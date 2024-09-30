#include "Tephra.hpp"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>

#include "Parser.hpp"
#include "Scanner.hpp"

#include "Expr.hpp"
#include "ExprPrinter.hpp"

int main(int argc, char** argv)
{
    if (argc == 1)
        tephra::runPrompt();
    else if (argc == 2)
        tephra::runFile(argv[1]);
    else
        std::cout << "Usage: <exec-filename> [<src-filename>]\n";
}

namespace tephra
{
void run(std::string&& source)
{
    Scanner scanner(std::move(source));
    auto& tokens = scanner.scanTokens();

    Parser parser(std::vector<Token>{tokens});
    auto expr = parser.parse();

    for (const auto& token : tokens)
        std::cout << token << "\n";

    if (expr)
        std::cout << "Parsed: " << std::visit(ExprPrinter{}, *expr) << "\n";
}

void runFile(const std::string& path)
{
    std::filesystem::path filePath(path);
    std::size_t fileSize = std::filesystem::file_size(filePath);
    std::ifstream file(filePath, std::ios::binary);

    run(std::string{std::istreambuf_iterator{file}, {}});
}

void runPrompt()
{
    std::cout << "========Tephra Prompt========\n";
    for (;;) {
        std::cout << "tephra> ";
        std::string line;
        std::getline(std::cin, line);
        if (line == "quit") break;
        run(std::move(line));
    }
}

void error(unsigned ln, unsigned ch, std::string&& msg)
{
    std::cerr << std::format("[{}:{}] Error: {}\n",
                             ln, ch, msg);
}
}
