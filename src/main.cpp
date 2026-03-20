#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "ast/lexer.hpp"
#include "token.hpp"

int main(int argc, char* argv[]) {
    // Receive the file path from the command-line arguments
    if (argc < 2) {
        std::cerr << "Usage: aegis <source_file.agis>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << file_path << std::endl;
        return 1;
    }

    // Read the entire contents of the file as a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source_code = buffer.str();

    std::cout << "--- Reading: " << file_path << " ---" << std::endl;

    // Pass to the lexer
    aegis::Lexer lexer(source_code);
    auto tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << "Line " << token.line << " | "
                  << "Type: " << static_cast<int>(token.type) << " | "
                  << "Literal: [" << token.literal << "]" << std::endl;
    }

    return 0;
}