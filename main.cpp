#include <algorithm>
#include <cctype>
#include <cstddef>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "Scanner.hpp"

static void run(std::string&& source);
static void runFile(std::string path);
static void runPrompt();

int main(int argc, char** argv)
{
    if (argc == 1)
        runPrompt();
    else if (argc == 2)
        runFile(argv[1]);
    else
        std::cout << "Usage: <exec-filename> [<src-filename>]\n";
}

static void run(std::string&& source)
{
    Scanner scanner(std::move(source));
    const auto& tokens = scanner.scanTokens();

    for (const auto& token : tokens)
        std::cout << "    | " << token << "\n";
}

static void runFile(std::string path)
{
    std::filesystem::path filePath(path);
    std::size_t fileSize = std::filesystem::file_size(filePath);
    std::ifstream file(filePath, std::ios::binary);

    using istream_iter = std::istreambuf_iterator<char>;
    run(std::string{istream_iter{file}, istream_iter{}});
}

static void runPrompt()
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
