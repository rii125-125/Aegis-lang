#include "parser.hpp"
#include <iostream>
#include <stdexcept>

namespace aegis {
    Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

    void Parser::parse() {
        try {
            while (!isAtEnd()) {
                declaration_to_node();
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Parse Error: " << e.what() << std::endl;
        }
    }

    std::unique_ptr<Stmt> Parser::declaration_to_node() {
        try {
            if (match({TokenType::FUN})) {
                // 解析した関数ノードをそのまま返す
                return functionDeclaration();
            }
            
            // 何もマッチしない場合はステートメントとして解析
            return statement_to_node();
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in declaration: " << e.what() << std::endl;
            advance(); // エラー時は1つ進めて復帰を試みる
            return nullptr;
        }
    }

    std::unique_ptr<Stmt> Parser::functionDeclaration() {
        Token name = consume(TokenType::IDENTIFIER, "Expect function name.");
        
        // トークン名は定義に合わせて L_PAREN か LEFT_PAREN か確認してください
        consume(TokenType::L_PAREN, "Expect '(' after function name.");
        consume(TokenType::R_PAREN, "Expect ')' after parameters.");
        consume(TokenType::L_BRACE, "Expect '{' before function body.");

        std::vector<std::unique_ptr<Stmt>> body;
        while (!check(TokenType::R_BRACE) && !isAtEnd()) {
            auto stmt = statement_to_node();
            if (stmt != nullptr) {
                body.push_back(std::move(stmt));
            }
        }

        consume(TokenType::R_BRACE, "Expect '}' after function body.");
        return std::make_unique<FunctionStmt>(std::move(name), std::move(body));
    }

    std::unique_ptr<Stmt> Parser::statement_to_node() {
        // print( ... ); の解析
        if (check(TokenType::IDENTIFIER) && peek().lexeme == "print") {
            advance(); // 'print' を消費
            return printStatement();
        }

        // 何にも当てはまらない場合は、トークンを消費してNULLを返す（ぬるぽ回避のためmain側でチェックが必要）
        if (!isAtEnd()) advance();
        return nullptr;
    }

    std::unique_ptr<Stmt> Parser::printStatement() {
        consume(TokenType::L_PAREN, "Expect '(' after 'print'.");
        
        // 文字列リテラルを取得
        Token value = consume(TokenType::STRING_LITERAL, "Expect string literal.");
        
        consume(TokenType::R_PAREN, "Expect ')' after arguments.");
        consume(TokenType::SEMICOLON, "Expect ';' after statement.");

        return std::make_unique<PrintStmt>(value.lexeme);
    }

    // --- 補助メソッド群 ---

    Token Parser::consume(TokenType type, std::string message) {
        if(check(type)) return advance();
        throw std::runtime_error(message);
    }

    bool Parser::match(std::vector<TokenType> types) {
        for (auto type : types) {
            if(check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    bool Parser::isAtEnd() {
        return current >= tokens.size() || peek().type == TokenType::END_OF_FILE;
    }

    bool Parser::check(TokenType type) {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    Token Parser::peek() {
        return tokens[current];
    }

    Token Parser::advance() {
        if (!isAtEnd()) current++;
        return previous();
    }

    Token Parser::previous() {
        return tokens[current - 1];
    }
}