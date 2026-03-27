#ifndef AEGIS_TOKEN_HPP
#define AEGIS_TOKEN_HPP

#include <string>
#include <vector>

namespace aegis {
    /**
     * トークンリスト。ここで、すべてのキーワードが字句解析へ活用される。
    */
    enum class TokenType {
        // 制御・記号
        L_PAREN, // (
        R_PAREN, // )
        L_BRACE, // {
        R_BRACE, // }
        L_BRACKET, // [
        R_BRACKET, // ]
        COLON, // :
        SEMICOLON, // ;
        COMMA, DOT, // , .
        ASTERISK,  // **

        // 演算子
        ASSIGN, // =
        MAGIC_ASSIGN, // #=
        PLUS, // +
        MINUS, // -
        MUL, // **
        DIV, // /
        MOD, // %

        // 論理演算
        EQ, // ==
        NE, // !=
        LT, // <
        GT, // >
        LE,// <=
        GE, // >=
        AND, // &&
        OR, // ||
        NOT, // !

        // キーワード
        FUN, // fun
        MAIN, // main
        IF, // if
        ELSE, // else
        FOR, // for
        SWITCH, // switch
        IMPORT, // import
        NEW, // new
        LIST, // list
        ENUM, // enum
        OPEN, // open
        CLOSE, // close
        ERROR_RETURN, // error.return
        DETACH, // $detach

        // アクセス権
        WTR, // writer
        RDR, // reader
        LCK, // lock
        VLT, // vault
        WTL, // write_limited
        RDL, // read_limited

        // リテラル・識別子
        IDENTIFIER, // 変数名や関数名
        INT_LITERAL, // int
        FLOAT_LITERAL, // float
        STRING_LITERAL, // string
        CHAR_LITERAL, // char
        BOOL_LITERAL, // boolean

        // アノテーション
        ANNOTATION, // @

        // その他
        END_OF_FILE, // EOF
        UNKNOWN, // 解析不能
    };

    struct Token {
        TokenType type;
        std::string lexeme;
        int line;
    };
};

#endif