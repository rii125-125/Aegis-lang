#pragma once
#include "token.hpp"
#include <vector>
#include <string_view>

namespace aegis {

class Lexer {
public:
    explicit Lexer(std::string_view source);

    // 全てのトークンを解析してリストで返す
    std::vector<Token> tokenize();

private:
    std::string_view source_;
    size_t cursor_ = 0; // 現在読み込んでいる位置
    int line_ = 1;      // 現在の行番号（エラー表示用）

    // ユーティリティ関数
    char peek() const;      // 次の文字を見る
    char advance();         // 一文字進めて、その文字を返す
    bool is_at_end() const; // 最後まで読んだか
    void skip_whitespace(); // 空白や改行を飛ばす

    Token make_token(TokenType type, std::string_view literal);
    Token scan_identifier(); // 英数字（キーワード含む）を解析
    Token scan_string();     // 文字列リテラルを解析
};

} // namespace aegis