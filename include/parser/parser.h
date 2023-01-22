#pragma once

#include "lexer/lexer.h"
#include <queue>

class Parser {
    public:
        static bool checkForReservedSymbols (std::string symbol);
        static bool checkForTypeSymbols     (std::string symbol);

        class Parameter {
            private:
                std::string type;
                std::string name;
            public:
                Parameter();
                Parameter(std::string name);
                Parameter(std::string type, std::string name);

                void        setType(std::string type);
                void        setName(std::string name);
                std::string getType();
                std::string getName();
                std::string getInfo();

                void print  ();

                static std::vector<Parser::Parameter> parse(std::queue<Lexer::Token> &q);
        };

        class Port {
            private:
                std::string                 direction;
                std::string                 implementation;
                std::string                 type;
                std::vector<std::string>    params;
                std::string                 name;
            public:
                Port();
                Port(std::string name);
                Port(std::string type, std::string name);
                Port(std::string type, std::vector<std::string> params, std::string name);
                Port(std::string direction, std::string type, std::string name);
                Port(std::string direction, std::string type, std::vector<std::string> params, std::string name);
                Port(std::string direction, std::string implementation, std::string type, std::string name);
                Port(std::string direction, std::string implementation, std::string type, std::vector<std::string> params, std::string name);

                void setDirection       (std::string direction);
                void setImplementation  (std::string implementation);
                void setType            (std::string type);
                void setParams          (std::vector<std::string> params);
                void appendParam        (std::string param);
                void clearParams        ();
                void setName            (std::string name);

                std::string                 getDirection        ();
                std::string                 getImplementation   ();
                std::string                 getType             ();
                std::vector<std::string>    getParams           ();
                std::string                 getParam            (int idx);
                std::string                 getName             ();
                std::string                 getInfo             ();

                void print();

                static std::vector<Parser::Port> parse(std::queue<Lexer::Token> &q);
        };

        class Pipe {
            public:
                class Instance {
                    private:
                        std::string pipe;
                        std::string name;
                    public:
                        Instance();
                        static Parser::Pipe::Instance parse(std::queue<Lexer::Token> &q);
                };

            private:
                std::string                         name;
                std::vector<Parser::Parameter>      params;
                std::vector<Parser::Port>           ports;
                std::vector<Parser::Pipe::Instance> instances;
            public:


                Pipe();
                Pipe(std::string name);
                Pipe(std::string name, std::vector<Parser::Parameter> params);
                Pipe(std::string name, std::vector<Parser::Port> ports);
                Pipe(std::string name, std::vector<Parser::Parameter> params, std::vector<Parser::Port> ports);

                void setName    (std::string name);
                void setParams  (std::vector<Parser::Parameter>  params);
                void appendParam(Parser::Parameter param);
                void clearParams();
                void setPorts   (std::vector<Parser::Port> ports);
                void appendPort (Parser::Port port);
                void clearPorts ();

                std::string                     getName     ();
                std::vector<Parser::Parameter>  getParams   ();
                Parser::Parameter               getParam    (int idx);
                std::vector<Parser::Port>       getPorts    ();
                Parser::Port                    getPort     (int idx);
                std::string                     getInfo     ();

                void print();

                static Parser::Pipe parse (std::queue<Lexer::Token> &q);
        };

    private:
        std::vector<Parser::Pipe> pipes;
    public:
        Parser (std::vector<Lexer::Token> tokens);
};