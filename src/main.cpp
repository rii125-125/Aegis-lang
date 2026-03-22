#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ast/lexer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: aegis <source_file.agis>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source_code = buffer.str();

    aegis::Lexer lexer(source_code);
    auto tokens = lexer.tokenize();

    std::cout << "--- Executing Aegis ---" << std::endl;

    for (size_t i = 0; i < tokens.size(); ++i) {
        // 1. 'print' を見つける
        if (tokens[i].type == aegis::TokenType::Print) {
            
            // 2. 次が '(' であることを確認
            if (i + 1 < tokens.size() && tokens[i + 1].type == aegis::TokenType::LParen) {
                
                // 3. その次が "文字列" であることを確認
                if (i + 2 < tokens.size() && tokens[i + 2].type == aegis::TokenType::String) {
                    
                    // 4. その次が ')' であることを確認
                    if (i + 3 < tokens.size() && tokens[i + 3].type == aegis::TokenType::RParen) {
                        
                        // 実行！
                        std::cout << tokens[i + 2].literal << std::endl;
                        
                        // 解析した分（( "text" )）だけインデックスを進める
                        i += 3; 
                    }
                }
            }
        }
    }

    std::cout << "-----------------------" << std::endl;
    return 0;
}