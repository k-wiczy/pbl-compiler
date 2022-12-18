#include "lexer/lexer.h"

std::string Lexer::Token::tokenType2Str(TokenType token) {
    if (token == TokenType::TOKEN_SYMBOL) {
        return "Symbol";
    } else if (token == TokenType::TOKEN_STRING_LITERAL) {
        return "String Literal";
    } else if (token == TokenType::TOKEN_NUMERIC_LITERAL) {
        return "Numeric Literal";
    } else if (token == TokenType::TOKEN_OPERATOR) {
        return "Operator";
    } else if (token == TokenType::TOKEN_PREPROCESSOR) {
        return "Preprocessor";
    } else {
        return "None";
    }
}

Lexer::Token::Token(int line, int column, TokenType type, std::string value) {
    this->line      = line;
    this->column    = column;
    this->value     = value;
    this->type      = type;
}

std::string Lexer::Token::Info() {
    return "[Line = " + std::to_string(this->line) + " \tColumn = " + std::to_string(this->column) + "\t]: " + this->tokenType2Str(this->type) + " = " + this->value;
}

void Lexer::doDualTokenBuffer(std::string &buf, std::string in) {
    if (buf.length() > 0) {
        buf = buf.substr(buf.length()-1, 1) + in.substr(0, 1);
    } else {
        buf = in.substr(0, 1);
    }
}

Lexer::Lexer(std::string source) {
    std::ifstream file (std::filesystem::path(source).string());

    bool string_token               = false;
    bool preprocessor_token         = false;
    bool numeric_token              = false;
    bool line_comment               = false;
    bool block_comment              = false;
    std::string dual_token_buffer   = "";

    if (file.is_open()) {
        char c;
        std::string buffer = "";

        int line = 1;
        int col  = 1;

        while(file.get(c)) {
            doDualTokenBuffer(dual_token_buffer, std::string(&c));
            if (dual_token_buffer == "//") {
                line_comment = true;
            } else if (dual_token_buffer == "/*") {
                block_comment = true;
            }

            if (!(line_comment || block_comment)) {
                if (dual_token_buffer.length() == 2) {
                    if (dual_token_buffer.substr(0,1) == "/" && (dual_token_buffer.substr(1,1) != "/" && dual_token_buffer.substr(1,1) != "*")) {
                        tokens.push_back(Token(line, col, Token::TokenType::TOKEN_OPERATOR, "/"));
                    } else if (dual_token_buffer.substr(0,1) == "-") {
                        if (dual_token_buffer.substr(1,1) == "0" ||
                            dual_token_buffer.substr(1,1) == "1" ||
                            dual_token_buffer.substr(1,1) == "2" ||
                            dual_token_buffer.substr(1,1) == "3" ||
                            dual_token_buffer.substr(1,1) == "4" ||
                            dual_token_buffer.substr(1,1) == "5" ||
                            dual_token_buffer.substr(1,1) == "6" ||
                            dual_token_buffer.substr(1,1) == "7" ||
                            dual_token_buffer.substr(1,1) == "8" ||
                            dual_token_buffer.substr(1,1) == "9") {
                            numeric_token = true;
                        }
                    } else {
                        if (dual_token_buffer.substr(1,1) == "0" ||
                            dual_token_buffer.substr(1,1) == "1" ||
                            dual_token_buffer.substr(1,1) == "2" ||
                            dual_token_buffer.substr(1,1) == "3" ||
                            dual_token_buffer.substr(1,1) == "4" ||
                            dual_token_buffer.substr(1,1) == "5" ||
                            dual_token_buffer.substr(1,1) == "6" ||
                            dual_token_buffer.substr(1,1) == "7" ||
                            dual_token_buffer.substr(1,1) == "8" ||
                            dual_token_buffer.substr(1,1) == "9") {
                            numeric_token = true;
                        }
                    }
                }

                bool match = false;
                if (!match && !string_token) {
                    for (auto _c : this->white_char) {
                        if (c == _c) {
                            match = true;
                            if (buffer.length() > 0) {
                                if (preprocessor_token) {
                                    tokens.push_back(Token(line, col, Token::TokenType::TOKEN_PREPROCESSOR, buffer));
                                    buffer = "";
                                    preprocessor_token = false;
                                } else if (numeric_token) {
                                    if (c != '.') {
                                        tokens.push_back(Token(line, col, Token::TokenType::TOKEN_NUMERIC_LITERAL, buffer));
                                        numeric_token = false;
                                        buffer = "";
                                    } else {
                                        buffer += std::string(&c);
                                    }
                                } else {
                                    tokens.push_back(Token(line, col, Token::TokenType::TOKEN_SYMBOL, buffer));
                                    buffer = "";
                                }
                            }
                        }
                    }
                }
                if (!match) {
                    for (auto _c : this->special_char) {
                        if (c == _c) {
                            match = true;
                            if (c == '\"') {
                                if (!string_token) {
                                    string_token = true;
                                } else {
                                    string_token = false;
                                    tokens.push_back(Token(line, col, Token::TokenType::TOKEN_STRING_LITERAL, buffer));
                                    buffer = "";
                                }
                            } else if (c == '#') {
                                preprocessor_token = true;
                            } else if (c != '/') {
                                if (buffer.length() > 0 && !string_token) {
                                    if (numeric_token) {
                                        if (c != '.') {
                                            tokens.push_back(Token(line, col, Token::TokenType::TOKEN_NUMERIC_LITERAL, buffer));
                                            numeric_token = false;
                                            tokens.push_back(Token(line, col, Token::TokenType::TOKEN_OPERATOR, std::string(&c)));
                                            buffer = "";
                                        } else {
                                            buffer += std::string(&c);
                                        }
                                    } else {
                                        tokens.push_back(Token(line, col, Token::TokenType::TOKEN_SYMBOL, buffer));
                                        tokens.push_back(Token(line, col, Token::TokenType::TOKEN_OPERATOR, std::string(&c)));
                                        buffer = "";
                                    }
                                } else if (string_token) {
                                    buffer += std::string(&c);
                                } else {
                                    tokens.push_back(Token(line, col, Token::TokenType::TOKEN_OPERATOR, std::string(&c)));
                                }
                            }
                            
                        }
                    }
                }
                if (!match) {
                    buffer += std::string(&c);
                }
            }

            if (dual_token_buffer == "*/") {
                block_comment = false;
                dual_token_buffer = "";
            } else if (c == '\n') {
                line_comment = false;
                dual_token_buffer = "";
            }

            if (c == '\n') {
                line++;
                col = 0;
            } else {
                col++;
            }
        }
    }

    file.close();
}

void Lexer::Info() {
    for (auto token : tokens) {
        std::cout << token.Info() << std::endl;
    }
}

std::vector<Lexer::Token> Lexer::GetTokens() {
    return this->tokens;
}