#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <list>

class Lexer {
    public:
        class Token {
            public:
                enum class TokenType {
                    TOKEN_SYMBOL,
                    TOKEN_STRING_LITERAL,
                    TOKEN_NUMERIC_LITERAL,
                    TOKEN_PREPROCESSOR,
                    TOKEN_OPERATOR
                };
 
                std::string tokenType2Str(TokenType token);

            private:
                int         line;
                int         column;
                TokenType   type;
                std::string value;
                
            public:
                Token(int line, int column, TokenType type, std::string value = "");
                std::string Info();
                TokenType   GetType() { return this->type; }
                std::string GetValue() { return this->value; }
        };

    private:
        std::vector<Token>  tokens;

        std::list<char>     special_char = std::list<char>({
            '{', '}', ')', '(', '<', '>', ',', '.', ';', '+', '=', '/', '*', '#', '\"'
        });

        std::list<char>     white_char   = std::list<char>({
            ' ', '\n', '\t', '\r'
        });

        void                doDualTokenBuffer   (std::string &buf, std::string in);

    public:
                            Lexer               (std::string source);
        void                Info                ();
        std::vector<Token>  GetTokens           ();
};