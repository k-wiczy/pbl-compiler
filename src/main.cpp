#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include "lexer/lexer.h"
#include "parser/parser.h"

int main(int argc, char ** argv) {
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }

    Lexer lexer (args[1]);
    Parser parser (lexer.GetTokens());
}