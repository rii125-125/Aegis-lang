#ifndef AEGIS_PARSER_HPP
#define AEGIS_PARSER_HPP

#include "../token.hpp"
#include "ast_nodes.hpp"
#include <vector>
#include <memory>
#include <string>

namespace aegis {
    class Parser {
        public:
            Parser(const std::vector<Token>& tokens);

            void parse();
            std::unique_ptr<Stmt> declaration_to_node();
            Token peek();

        private:
            std::vector<Token> tokens;
            int current = 0;
            std::unique_ptr<Stmt> functionDeclaration();
            std::unique_ptr<Stmt> statement_to_node();
            std::unique_ptr<Stmt> printStatement();

            bool isAtEnd();
            Token advance();
            bool check(TokenType type);
            bool match(std::vector<TokenType> types);
            Token previous();
            Token consume(TokenType type, std::string message);
    };
}
#endif