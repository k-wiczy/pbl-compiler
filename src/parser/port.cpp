#include "parser/parser.h"

Parser::Port::Port() {
    this->direction         = "input";
    this->implementation    = "control";
    this->type              = "bit";
    this->params            = std::vector<std::string>();
    this->name              = "undefined";
}

Parser::Port::Port(std::string name) {
    this->direction         = "input";
    this->implementation    = "control";
    this->type              = "bit";
    this->params            = std::vector<std::string>();
    this->name              = name;
}

Parser::Port::Port(std::string type, std::string name) {
    this->direction         = "input";
    this->implementation    = "control";
    this->type              = type;
    this->params            = std::vector<std::string>();
    this->name              = name;
}

Parser::Port::Port(std::string type, std::vector<std::string> params, std::string name) {
    this->direction         = "input";
    this->implementation    = "control";
    this->type              = type;
    this->params            = params;
    this->name              = name;
}

Parser::Port::Port(std::string direction, std::string type, std::string name) {
    this->direction         = direction;
    this->implementation    = "control";
    this->type              = type;
    this->params            = std::vector<std::string>();
    this->name              = name;
}

Parser::Port::Port(std::string direction, std::string type, std::vector<std::string> params, std::string name) {
    this->direction         = direction;
    this->implementation    = "control";
    this->type              = type;
    this->params            = params;
    this->name              = name;
}

Parser::Port::Port(std::string direction, std::string implementation, std::string type, std::string name) {
    this->direction         = direction;
    this->implementation    = implementation;
    this->type              = type;
    this->params            = std::vector<std::string>();
    this->name              = name;
}

Parser::Port::Port(std::string direction, std::string implementation, std::string type, std::vector<std::string> params, std::string name){
    this->direction         = direction;
    this->implementation    = implementation;
    this->type              = type;
    this->params            = params;
    this->name              = name;
}

void Parser::Port::setDirection(std::string direction) {
    this->direction = direction;
}

void Parser::Port::setImplementation(std::string implementation) {
    this->implementation = implementation;
}
    
void Parser::Port::setType(std::string type) {
    this->type = type;
}

void Parser::Port::setParams(std::vector<std::string> params) {
    this->params = params;
}

void Parser::Port::appendParam(std::string param) {
    this->params.push_back(param);
}

void Parser::Port::clearParams() {
    this->params.clear();
}

void Parser::Port::setName(std::string name) {
    this->name = name;
}

std::string Parser::Port::getDirection() {
    return this->direction;
}

std::string Parser::Port::getImplementation() {
    return this->implementation;
}

std::string Parser::Port::getType() {
    return this->type;
}

std::vector<std::string> Parser::Port::getParams() {
    return this->params;
}

std::string Parser::Port::getParam(int idx) {
    auto it = this->params.begin();
    std::advance(it, idx);
    return *it;
}

std::string Parser::Port::getName() {
    return this->name;
}

std::string Parser::Port::getInfo() {
    std::string ret = "";
    if (this->direction != "")      ret += this->direction;
    if (this->implementation != "") ret += " " + this->implementation;
    if (this->type != "")           ret += " " + this->type;

    if (this->params.size() > 0) {
        ret += " <";
        int idx = 0;
        for (auto p : this->params) {
            ret += p;
            if (++idx < this->params.size()) {
                ret += ", ";
            } else {
                ret += ">";
            }
        }
    }

    if (this->name != "")           ret += " " + this->name;

    return ret;
}

void Parser::Port::print() {
    std::cout << "[PORT] " << this->getInfo() << std::endl;
}

std::vector<Parser::Port> Parser::Port::parse(std::queue<Lexer::Token> &q) {
    std::vector<Parser::Port> ret;

    enum port_state_t {
        PORT_STATE_IDLE,
        PORT_STATE_DIRECTION,
        PORT_STATE_IMPLEMENTATION,
        PORT_STATE_TYPE,
        PORT_STATE_TYPE_PARAMETERS,
        PORT_STATE_TYPE_PARAMETERS_SEPARATOR,
        PORT_STATE_NAME,
        PORT_STATE_SEPARATOR
    };

    port_state_t port_state = PORT_STATE_IDLE;

    Parser::Port p;

    while(!q.empty()) {
        auto token = q.front();
        q.pop();

        if (port_state == PORT_STATE_IDLE) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_SYMBOL) {
                if (token.GetValue() == "input" || token.GetValue() == "output") {
                    p.setDirection(token.GetValue());
                    port_state = PORT_STATE_DIRECTION;
                } else if (token.GetValue() == "control" || token.GetValue() == "signal") {
                    p.setImplementation(token.GetValue());
                    port_state = PORT_STATE_IMPLEMENTATION;
                } else {
                    if (Parser::checkForTypeSymbols(token.GetValue())) {
                        p.setType(token.GetValue());
                        port_state = PORT_STATE_TYPE;
                    } else {
                        std::cerr << "Parser error: Unexpected reserved symbol: " << token.GetValue() << std::endl;
                        exit(-1);
                    }
                }
            } else {
                std::cerr << "Parser error: Unexpected " << Lexer::Token::tokenType2Str(token.GetType()) << std::endl;
                exit(-1);
            }
        } else if (port_state == PORT_STATE_DIRECTION) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_SYMBOL) {
                if (token.GetValue() == "control" || token.GetValue() == "signal") {
                    p.setImplementation(token.GetValue());
                    port_state = PORT_STATE_IMPLEMENTATION;
                } else {
                    if (Parser::checkForTypeSymbols(token.GetValue())) {
                        p.setType(token.GetValue());
                        port_state = PORT_STATE_TYPE;
                    } else {
                        std::cerr << "Parser error: Unexpected reserved symbol: " << token.GetValue() << std::endl;
                        exit(-1);
                    }
                }
            } else {
                std::cerr << "Parser error: Unexpected " << Lexer::Token::tokenType2Str(token.GetType()) << std::endl;
                exit(-1);
            }
        } else if (port_state == PORT_STATE_IMPLEMENTATION) {
            if (token.GetType() == Lexer::Token::TokenType::TOKEN_SYMBOL) {
                if (Parser::checkForTypeSymbols(token.GetValue())) {
                        p.setType(token.GetValue());
                        port_state = PORT_STATE_TYPE;
                } else {
                        std::cerr << "Parser error: Unexpected reserved symbol: " << token.GetValue() << std::endl;
                        exit(-1);
                }
            } else {
                std::cerr << "Parser error: Unexpected " << Lexer::Token::tokenType2Str(token.GetType()) << std::endl;
                exit(-1);
            }
        } else if (port_state == PORT_STATE_TYPE) {
            if (token.GetValue() == "<") {
                port_state = PORT_STATE_TYPE_PARAMETERS;
            } else if (!Parser::checkForReservedSymbols(token.GetValue())) {
                p.setName(token.GetValue());
                port_state = PORT_STATE_SEPARATOR;
            } else {
                std::cerr << "Parser error: Unexpected reserved symbol: " << token.GetValue() << std::endl;
                exit(-1);
            }
        } else if (port_state == PORT_STATE_TYPE_PARAMETERS) {
            if (!Parser::checkForReservedSymbols(token.GetValue())) {
                p.appendParam(token.GetValue());
                port_state = PORT_STATE_TYPE_PARAMETERS_SEPARATOR;
            } else {
                std::cerr << "Parser error: Unexpected reserved symbol: " << token.GetValue() << std::endl;
                exit(-1);
            }
        } else if (port_state == PORT_STATE_TYPE_PARAMETERS_SEPARATOR) {
            if (token.GetValue() == ",") {
                port_state = PORT_STATE_TYPE_PARAMETERS;
            } else if (token.GetValue() == ">") {
                port_state = PORT_STATE_NAME;
            }
        } else if (port_state == PORT_STATE_NAME) {
            if (!Parser::checkForReservedSymbols(token.GetValue())) {
                p.setName(token.GetValue());
                port_state = PORT_STATE_SEPARATOR;
            } else {
                std::cerr << "Parser error: Unexpected reserved symbol: " << token.GetValue() << std::endl;
                exit(-1);
            }
        } else if (port_state == PORT_STATE_SEPARATOR) {
            if (token.GetValue() == ",") {
                port_state = PORT_STATE_IDLE;
                ret.push_back(p);
                p = Parser::Port();
            } else if (token.GetValue() == ")") {
                ret.push_back(p);
                break;
            } else {
                std::cerr << "Parser error: Unexpected symbol: " << token.GetValue() << std::endl;
                exit(-1);
            }
        }
    }
    
    return ret;
}