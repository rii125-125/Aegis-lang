#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

#include "ast/lexer.hpp"
#include "./syntax/parser.hpp"
#include "runtime/interpreter.hpp"

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

    aegis::Parser parser(tokens);
    std::vector<std::unique_ptr<aegis::Stmt>> program;

    try {
        while (parser.peek().type != aegis::TokenType::END_OF_FILE) {
            program.push_back(parser.declaration_to_node());
        }
    } catch (const std::exception& e) {
        std::cerr << "Aegis Compile Error: " << e.what() << std::endl;
        return 1;
    }

    // ? Debug
    std::cout << "Debug: Nodes parsed: " << program.size() << std::endl;

    std::cout << "--- Execution Start ---" << std::endl;
    aegis::Interpreter interpreter;
    interpreter.interpret(program);
    std::cout << "----------------------" << std::endl;

    return 0;
}