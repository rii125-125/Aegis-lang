#ifndef AEGIS_LEXER_HPP
#define AEGIS_LEXER_HPP

#include "../token.hpp"
#include <string>
#include <vector>
#include <map>

namespace aegis
{
    class Lexer
    {
    public:
        // ソースコードを注入して初期化
        Lexer(const std::string &source);

        // すべてのトークンを解析して返却
        std::vector<Token> scanTokens();

    private:
        std::string source;
        std::vector<Token> tokens;

        // 解析状態
        int start = 0;
        int current = 0;
        int line = 1;

        // 予約語の検索用マップ
        static const std::map<std::string, TokenType> keywords;

        // ヘルパー
        bool isAtEnd();
        char advance();
        char peek();
        char peekNext();
        bool match(char expencted);

        // トークン作成
        void scanToken();
        void addToken(TokenType type);
        void addToken(TokenType type, std::string lexeme);

        // パターンマッチング
        void identifier();
        void number();
        void stringLiteral();
    };
}

#endif