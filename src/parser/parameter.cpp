#include "parser/parser.h"

Parser::Parameter::Parameter() {
    this->type = "auto";
    this->name = "undefined";
}

Parser::Parameter::Parameter(std::string name) {
    this->type = "auto";
    this->name = name;
}

Parser::Parameter::Parameter(std::string  type, std::string name) {
    this->type = type;
    this->name = name;
}

void Parser::Parameter::setType(std::string type) {
    this->type = type;
}

void Parser::Parameter::setName(std::string name) {
    this->name = name;
}

std::string Parser::Parameter::getType() {
    return this->type;
}

std::string Parser::Parameter::getName() {
    return this->name;
}

std::string Parser::Parameter::getInfo() {
    return this->type + ":" + this->name;
}

void Parser::Parameter::print() {
    std::cout << "[PARAMETER] " << this->getInfo() << std::endl;
}

std::vector<Parser::Parameter> Parser::Parameter::parse(std::queue<Lexer::Token> &q) {
    std::vector<Parser::Parameter> ret;
    std::string type, name;

    enum parameter_state_t {
        PARAMETER_STATE_IDLE,
        PARAMETER_STATE_TYPE,
        PARAMETER_STATE_NAME
    };

    parameter_state_t param_state = PARAMETER_STATE_IDLE;

    while(!q.empty()) {
        auto token = q.front();
        q.pop();

        if (param_state == PARAMETER_STATE_IDLE) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_SYMBOL) {
                type = token.GetValue();
                param_state = PARAMETER_STATE_TYPE;
            } else if (token.GetType() == Lexer::Token::TokenType::TOKEN_OPERATOR) {
                if (token.GetValue() == ">") {
                    return ret;
                } else {
                    std::cerr << "Parser error: Unexpected operator: " << token.GetValue() << std::endl;
                    exit(-1);
                }
            }
        } else if (param_state == PARAMETER_STATE_TYPE) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_SYMBOL) {
                if (!checkForReservedSymbols(token.GetValue())) {
                    name = token.GetValue();
                    ret.push_back(Parser::Parameter(type, name));
                    param_state = PARAMETER_STATE_NAME;
                } else {
                    std::cerr << "Parser error: Unexpected reserved symbol: " << token.GetValue() << std::endl;
                    exit(-1);
                }
            }
        } else if (param_state == PARAMETER_STATE_NAME) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_OPERATOR) {
                if (token.GetValue() == ",") {
                    param_state = PARAMETER_STATE_IDLE;
                } else if (token.GetValue() == ">") {
                    param_state = PARAMETER_STATE_IDLE;
                    return ret;
                } else {
                    std::cerr << "Parser error: Unexpected operator: " << token.GetValue() << std::endl;
                    exit(-1);
                }
            }
        }
    }

    return ret;
}