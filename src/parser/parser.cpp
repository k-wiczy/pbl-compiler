#include "parser/parser.h"

bool Parser::checkForReservedSymbols(std::string symbol) {
    std::vector<std::string> reserved = std::vector<std::string>({
        "pipe",
        "meminit",
        "apply",
        "connect",
        "include",
        "define",
        "int",
        "uint",
        "bit",
        "fix",
        "fp"
    });

    for (auto keyword : reserved) {
        if (symbol == keyword) {
            return true;
        }
    }
    return false;
}

bool Parser::checkForTypeSymbols(std::string symbol) {
    std::vector<std::string> reserved = std::vector<std::string>({
        "int",
        "uint",
        "bit",
        "fix",
        "fp"
    });

    for (auto keyword : reserved) {
        if (symbol == keyword) {
            return true;
        }
    }
    return false;    
}

Parser::Parser (std::vector<Lexer::Token> tokens) {
    std::queue<Lexer::Token> q;
    for (auto token : tokens) {
        q.push(token);
    }

    while (!q.empty()) {
        auto token = q.front();

        if (token.GetType() == Lexer::Token::TokenType::TOKEN_SYMBOL) {
            if (token.GetValue() == "pipe") {
                this->pipes.push_back(Parser::Pipe::parse(q));
            } else {
                std::cerr << "Parser error: Unexpected symbol: " << token.GetValue() << std::endl;
                exit(-1);
            }
        } else if (token.GetType() == Lexer::Token::TokenType::TOKEN_PREPROCESSOR) {
            q.pop();
        } else {
            std::cerr << "Parser error: Unexpected " << Lexer::Token::tokenType2Str(token.GetType()) << std::endl;
            exit(-1);
        }
    }

    for (auto p : pipes) {
        p.print();
    }
}