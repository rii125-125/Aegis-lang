#pragma once
#include <string>
#include <string_view>

namespace aegis {
    enum class TokenType {
        // Symbol
        LParen,    // (
        RParen,    // )
        LBrace,    // {
        RBrace,    // }
        Colon,     // :
        Equal,     // =
        Semicolon, // ;

        // Keywords
        Fun,
        Print,
        // Access rights
        Wtr, // writer
        Rdr, // reader
        Lck, // lock
        Vlt, // vault
        Wtl, // write_limited
        Rdl, // read_limited

        // Literals and identifiers
        Identifier, // Variable names and function names
        Number,     // number
        String,     // string

        // Special
        Eof,        // End of file
        Unknown     // Unknown token
    };

    struct Token {
        TokenType type;
        std::string_view literal; // Refers to a string in the source code
        int line;                 // It would be helpful to record the line number for error messages
    };
} // namespace aegis