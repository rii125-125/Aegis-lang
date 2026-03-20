#include "lexer.hpp"
#include <cctype>

namespace aegis {

Lexer::Lexer(std::string_view source) : source_(source) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!is_at_end()) {
        skip_whitespace();
        if (is_at_end()) break;

        char c = advance();
        if (std::isalpha(c) || c == '_') {
            tokens.push_back(scan_identifier());
        } else if (std::isdigit(c)) {
            // 数値リテラルの解析（今回は簡易版）
            size_t start = cursor_ - 1;
            while (std::isdigit(peek())) advance();
            tokens.push_back(make_token(TokenType::Number, source_.substr(start, cursor_ - start)));
        } else if (c == '"') {
            tokens.push_back(scan_string());
        } else {
            // 記号の判定
            switch (c) {
                case '(': tokens.push_back(make_token(TokenType::LParen, "(")); break;
                case ')': tokens.push_back(make_token(TokenType::RParen, ")")); break;
                case '{': tokens.push_back(make_token(TokenType::LBrace, "{")); break;
                case '}': tokens.push_back(make_token(TokenType::RBrace, "}")); break;
                case ';': tokens.push_back(make_token(TokenType::Semicolon, ";")); break;
                case '=': tokens.push_back(make_token(TokenType::Equal, "=")); break;
                case ':': tokens.push_back(make_token(TokenType::Colon, ":")); break;
                default:  tokens.push_back(make_token(TokenType::Unknown, source_.substr(cursor_-1, 1))); break;
            }
        }
    }
    tokens.push_back(make_token(TokenType::Eof, ""));
    return tokens;
}

Token Lexer::scan_identifier() {
    size_t start = cursor_ - 1;
    while (std::isalnum(peek()) || peek() == '_') advance();
    std::string_view text = source_.substr(start, cursor_ - start);

    // キーワード判定
    if (text == "fun")    return make_token(TokenType::Fun, text);
    if (text == "print")  return make_token(TokenType::Print, text);
    if (text == "wtr")    return make_token(TokenType::Wtr, text);
    if (text == "rdr")    return make_token(TokenType::Rdr, text);
    if (text == "lck")    return make_token(TokenType::Lck, text);
    if (text == "vlt")    return make_token(TokenType::Vlt, text);
    if (text == "wtl")    return make_token(TokenType::Wtl, text);
    if (text == "rdl")    return make_token(TokenType::Rdl, text);

    return make_token(TokenType::Identifier, text);
}

Token Lexer::scan_string() {
    size_t start = cursor_;
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') line_++;
        advance();
    }
    std::string_view text = source_.substr(start, cursor_ - start);
    advance(); // 閉じる側の " を飛ばす
    return make_token(TokenType::String, text);
}

// ユーティリティ
char Lexer::peek() const { return is_at_end() ? '\0' : source_[cursor_]; }
char Lexer::advance() { return source_[cursor_++]; }
bool Lexer::is_at_end() const { return cursor_ >= source_.size(); }
void Lexer::skip_whitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ': case '\r': case '\t': advance(); break;
            case '\n': line_++; advance(); break;
            default: return;
        }
    }
}
Token Lexer::make_token(TokenType type, std::string_view literal) {
    return {type, literal, line_};
}

} // namespace aegis