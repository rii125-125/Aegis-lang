#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "token.hpp"
#include "ast/lexer.hpp"

/**
 * Aegis Compiler Entry Point
 */
int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage: aegis [file.agis]" << std::endl;
        return 64;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    if(!file.is_open()) {
        std::cerr << "Error: Could not open file" << path << std::endl;
        return 66;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    aegis::Lexer lexer(source);
    std::vector<aegis::Token> tokens = lexer.scanTokens();

    std::cout << "--- Tokens Scanned ---" << std::endl;
    for (const auto& token : tokens) {
        std::cout << "Line" << token.line << ": [" << (int)token.type << "] " << token.lexeme << std::endl;
    }
    std::cout << "----------------------" << std::endl;

    return 0;
}