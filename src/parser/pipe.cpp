#include "parser/parser.h"

Parser::Pipe::Pipe() {
    this->name      = "undefined";
    this->params    = std::vector<Parser::Parameter>();
    this->ports     = std::vector<Parser::Port>();
}

Parser::Pipe::Pipe(std::string name) {
    this->name      = name;
    this->params    = std::vector<Parser::Parameter>();
    this->ports     = std::vector<Parser::Port>();
}

Parser::Pipe::Pipe(std::string name, std::vector<Parser::Parameter> params) {
    this->name      = name;
    this->params    = params;
    this->ports     = std::vector<Parser::Port>();
}

Parser::Pipe::Pipe(std::string name, std::vector<Parser::Port> ports) {
    this->name      = name;
    this->params    = std::vector<Parser::Parameter>();
    this->ports     = ports;
}

Parser::Pipe::Pipe(std::string name, std::vector<Parser::Parameter> params, std::vector<Parser::Port> ports) {
    this->name      = name;
    this->params    = params;
    this->ports     = ports;
}

void Parser::Pipe::setName(std::string name) {
    this->name = name;
}

void Parser::Pipe::setParams(std::vector<Parser::Parameter> params) {
    this->params = params;
}

void Parser::Pipe::appendParam(Parser::Parameter param) {
    this->params.push_back(param);
}

void Parser::Pipe::clearParams() {
    this->params.clear();
}

void Parser::Pipe::setPorts(std::vector<Parser::Port> ports) {
    this->ports = ports;
}

void Parser::Pipe::appendPort(Parser::Port port) {
    this->ports.push_back(port);
}

void Parser::Pipe::clearPorts() {
    this->ports.clear();
}

std::string Parser::Pipe::getName() {
    return this->name;
}

std::vector<Parser::Parameter> Parser::Pipe::getParams() {
    return this->params;
}

Parser::Parameter Parser::Pipe::getParam(int idx) {
    auto it = this->params.begin();
    std::advance(it, idx);
    return *it;
}

std::vector<Parser::Port> Parser::Pipe::getPorts() {
    return this->ports;
}

Parser::Port Parser::Pipe::getPort(int idx) {
    auto it = this->ports.begin();
    std::advance(it, idx);
    return *it;
}

std::string Parser::Pipe::getInfo() {
    std::string ret = "";

    ret += this->name + ":\n";
    
    ret += "- params:\n";
    for (auto p : this->params) {
        ret += "\t" + p.getInfo() + "\n";
    }

    ret += "- ports:\n";
    for (auto p : this->ports) {
        ret += "\t" + p.getInfo() + "\n";
    }

    return ret;
}

void Parser::Pipe::print() {
    std::cout << "[PIPE] " << this->getInfo() << std::endl; 
}

Parser::Pipe Parser::Pipe::parse(std::queue<Lexer::Token> &q) {
    Parser::Pipe ret;

    enum parser_state_t {
        PARSER_STATE_IDLE,
        PARSER_STATE_PIPE,
        PARSER_STATE_PIPE_NAME,
        PARSER_STATE_PIPE_PARAMETERS,
        PARSER_STATE_PIPE_BLOCK
    };

    parser_state_t state = PARSER_STATE_IDLE;

    while (!q.empty()) {
        auto token = q.front();
        q.pop();
        if (state == PARSER_STATE_IDLE) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_SYMBOL) {
                if (token.GetValue() == "pipe") {
                    state = PARSER_STATE_PIPE;
                } else {
                    std::cerr << "Pipe Parser error: Unexpected symbol: " << token.GetValue() << std::endl;
                    exit(-1);
                }
            } else {
                std::cerr << "Pipe Parser error: Unexpected " << Lexer::Token::tokenType2Str(token.GetType()) << std::endl;
                exit(-1);
            }
        } else if (state == PARSER_STATE_PIPE) {
            if (!Parser::checkForReservedSymbols(token.GetValue())) {
                ret.setName(token.GetValue());
                state = PARSER_STATE_PIPE_NAME;
            } else {
                std::cerr << "Pipe Parser error: Unexpected reserved symbol: " << token.GetValue() << std::endl;
                exit(-1);
            }
        } else if (state == PARSER_STATE_PIPE_NAME) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_OPERATOR) {
                if (token.GetValue() == "<") {
                    ret.setParams(Parser::Parameter::parse(q));
                } else if (token.GetValue() == "(") {
                    ret.setPorts(Parser::Port::parse(q));
                } else if (token.GetValue() == "{") {
                    state = PARSER_STATE_PIPE_BLOCK;
                } else if (token.GetValue() == ";") {
                    state = PARSER_STATE_IDLE;
                } else {
                    std::cerr << "Pipe Parser error: Unexpected operator: " << token.GetValue() << std::endl;
                    exit(-1);
                }
            } else {
                std::cerr << "Pipe Parser error: Unexpected " << Lexer::Token::tokenType2Str(token.GetType()) << std::endl;
                exit(-1);
            }
        } else if (state == PARSER_STATE_PIPE_BLOCK) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_SYMBOL) {
                if (token.GetValue() == "connect") {      
                    
                } else if (token.GetValue() == "apply") {

                } else if (!Parser::checkForReservedSymbols(token.GetValue()))  {

                } else {
                    std::cerr << "Pipe Parser error: Unexpected symbol: " << token.GetValue() << std::endl;
                    exit(-1);
                }
        }
    }

    return ret;
}