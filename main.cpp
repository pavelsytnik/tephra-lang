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

static void run(std::string source);
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

static void run(std::string source)
{
    std::istringstream iss(source);
    std::string token;

    while (iss >> token)
        if (std::ranges::all_of(token, [](auto c) {
            return std::isdigit(c);
        }))
            std::cout << std::format("Number <{}>\n", token);
        else
            std::cout << std::format("Something <{}>\n", token);
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
        run(line);
    }
}
