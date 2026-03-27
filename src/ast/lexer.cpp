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
        while (!isAtEnd()) {
            start = current;
            scanToken(); // ここで各トークンを解析
        }

        tokens.push_back({TokenType::END_OF_FILE, "", line});
        return tokens;
    }

    // 各文字を判定するコアメソッドを追加
    void Lexer::scanToken() {
        char c = advance();
        switch (c) {
            case '(': addToken(TokenType::L_PAREN); break;
            case ')': addToken(TokenType::R_PAREN); break;
            case '{': addToken(TokenType::L_BRACE); break;
            case '}': addToken(TokenType::R_BRACE); break;
            case '[': addToken(TokenType::L_BRACKET); break;
            case ']': addToken(TokenType::R_BRACKET); break;
            case ':': addToken(TokenType::COLON); break;
            case ';': addToken(TokenType::SEMICOLON); break;
            case ',': addToken(TokenType::COMMA); break;
            case '.': addToken(TokenType::DOT); break;
            case '*': addToken(TokenType::ASTERISK); break;
            case '=': addToken(match('=') ? TokenType::EQ : TokenType::ASSIGN); break;
            case '#': if (match('=')) addToken(TokenType::MAGIC_ASSIGN); break;
            case '$': identifier(); break; // $detach用
            case '@': addToken(TokenType::ANNOTATION); break;
            case ' ':
            case '\r':
            case '\t': break;
            case '\n': line++; break;
            case '"': stringLiteral(); break;
            default:
                if (isdigit(c)) {
                    number();
                } else if (isalpha(c) || c == '_') {
                    identifier();
                } else {
                    addToken(TokenType::UNKNOWN);
                }
                break;
        }
    }

    void Lexer::stringLiteral() {
        while (peek() != '"' && !isAtEnd()) {
            if(peek() == '\n') line++;
            advance();
        }
        if(isAtEnd()) return;
        advance(); // 閉じの "

        std::string value = source.substr(start + 1, current - start - 2);
        addToken(TokenType::STRING_LITERAL, value);
    }

    void Lexer::number() {
        while (isdigit(peek())) advance();
        if(peek() == '.' && isdigit(peekNext())) {
            advance();
            while (isdigit(peek())) advance(); // peek() に修正
            addToken(TokenType::FLOAT_LITERAL);
        } else {
            addToken(TokenType::INT_LITERAL);
        }
    }

    void Lexer::identifier() {
        while(isalnum(peek()) || peek() == '_' || peek() == '.') advance();
        std::string text = source.substr(start, current - start);

        if (text == "error.return") {
            addToken(TokenType::ERROR_RETURN);
            return;
        }
        if (text == "$detach") { // == に修正
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

    // --- 以下、ヘルパーメソッドは変更なし ---
    bool Lexer::isAtEnd() { return current >= source.length(); }
    char Lexer::advance() { return source[current++]; }
    char Lexer::peek() { return isAtEnd() ? '\0' : source[current]; }
    char Lexer::peekNext() { return (current + 1 >= source.length()) ? '\0' : source[current + 1]; }
    bool Lexer::match(char expected) {
        if (isAtEnd() || source[current] != expected) return false;
        current++;
        return true;
    }
    void Lexer::addToken(TokenType type) {
        tokens.push_back({type, source.substr(start, current - start), line});
    }
    void Lexer::addToken(TokenType type, std::string lexeme) {
        tokens.push_back({type, lexeme, line});
    }
}