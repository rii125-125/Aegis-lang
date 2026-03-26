#include "lexer.hpp"
#include <iostream>

namespace aegis {

    const std::map<std::string, TokenType> Lexer::keywords = {
        {"fun", TokenType::FUN},
        {"main", TokenType::MAIN},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"for", TokenType::FOR},
        {"switch", TokenType::SWITCH},
        {"import", TokenType::IMPORT},
        {"new", TokenType::NEW},
        {"list", TokenType::LIST},
        {"enum", TokenType::ENUM},
        {"open", TokenType::OPEN},
        {"close", TokenType::CLOSE},
        {"wtr", TokenType::WTR},
        {"rdr", TokenType::RDR},
        {"lck", TokenType::LCK},
        {"vlt", TokenType::VLT},
        {"wtl", TokenType::WTL},
        {"rdl", TokenType::RDL},
        {"true", TokenType::BOOL_LITERAL},
        {"false", TokenType::BOOL_LITERAL},
    };

    Lexer::Lexer(const std::string& source) : source(source) {}

    std::vector<Token> Lexer::scanTokens() {
        while (peek() != '"' && !isAtEnd()) {
            if(peek() == '\n') { line++ };
            advance();
        }

        tokens.push_back({TokenType::END_OF_FILE, "", line});
        return tokens;
    }

    void Lexer::stringLiteral() {
        while (peek() != '"' && !isAtEnd()) {
            if(peek() == '\n') { line++ };
            advance();
        }

        if(isAtEnd()) {
            return;
        }

        advance();

        std::string value = source.substr(start + 1, current -start -2);
        addToken(TokenType::STRING_LITERAL, value);
    }

    void Lexer::number() {
        while (isdigit(peek())) { advance() };

        if(peek() == '.' && isdigit(peekNext())) {
            advance();
            while (isdigit(peek)) { advance() };
            addToken(TokenType::FLOAT_LITERAL);
        } else {
            addToken(TokenType::INT_LITERAL);
        }
    }

    void Lexer::identifier() {
        while(isalnum(peek()) || peek() == '_' || peek() == '.') { advance() };

        std::string text = source.substr(start, current - start);

        if (text == "error.return") {
            addToken(TokenType::ERROR_RETURN);
            return;
        }
        if (text = "$detach") {
            addToken(TokenType::DETACH);
            return;
        }

        TokenType type = TokenType::IDENTIFIER;
        auto it = keywords.find(text);
        if (it != keywords.end()) {
            type = it->second;
        }

        addToken(type);
    }

    bool Lexer::isAtEnd() {
    return current >= source.length();
    }

    char Lexer::advance() {
        return source[current++];
    }

    char Lexer::peek() {
        if (isAtEnd()) return '\0';
        return source[current];
    }

    char Lexer::peekNext() {
        if (current + 1 >= source.length()) return '\0';
        return source[current + 1];
    }

    bool Lexer::match(char expected) {
        if (isAtEnd()) return false;
        if (source[current] != expected) return false;
        current++;
        return true;
    }

    void Lexer::addToken(TokenType type) {
        std::string text = source.substr(start, current - start);
        tokens.push_back({type, text, line});
    }

    void Lexer::addToken(TokenType type, std::string lexeme) {
        tokens.push_back({type, lexeme, line});
    }
}