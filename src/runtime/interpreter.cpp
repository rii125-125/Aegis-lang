#include <iostream>
#include "interpreter.hpp"

namespace aegis {
    void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
        const FunctionStmt* mainFunction = nullptr;

        std::cout << "Debug: Total statements to interpret: " << statements.size() << std::endl;

        for (size_t i = 0; i < statements.size(); ++i) {
            // 1. nullptrチェック
            if (statements[i] == nullptr) {
                std::cout << "Debug: Statement [" << i << "] is NULL pointer!" << std::endl;
                continue;
            }

            const Stmt* stmt = statements[i].get();
            
            // 2. typeid は使わず、dynamic_cast だけを試す
            const auto* funcStmt = dynamic_cast<const FunctionStmt*>(stmt);
            
            if (funcStmt) {
                std::cout << "Debug: Found FunctionStmt! Name lexeme: [" << funcStmt->name.lexeme << "]" << std::endl;

                if (funcStmt->name.lexeme == "main") {
                    mainFunction = funcStmt;
                    std::cout << "Debug: 'main' match success!" << std::endl;
                }
            } else {
                // 3. FunctionStmt じゃないなら、PrintStmt かな？
                if (dynamic_cast<const PrintStmt*>(stmt)) {
                    std::cout << "Debug: Statement [" << i << "] is a PrintStmt (not a function)." << std::endl;
                } else {
                    std::cout << "Debug: Statement [" << i << "] is an unknown Stmt type." << std::endl;
                }
            }
        }

        if (mainFunction) {
            std::cout << "Debug: Executing main... Body size: " << mainFunction->body.size() << std::endl;
            for (const auto& s : mainFunction->body) {
                if (s) execute(s.get());
            }
        } else {
            std::cerr << "Runtime Error: No 'main' function found." << std::endl;
        }
    }

    void Interpreter::execute(const Stmt* stmt) {
        if (!stmt) return;
        
        // ここでも dynamic_cast を使用
        if (const auto* s = dynamic_cast<const FunctionStmt*>(stmt)) {
            executeFunction(s);
        } else if (const auto* s = dynamic_cast<const PrintStmt*>(stmt)) {
            executePrint(s);
        }
    }

    void Interpreter::executeFunction(const FunctionStmt* stmt) {
        if (!stmt) return;
        for (const auto& s : stmt->body) {
            if (s) execute(s.get());
        }
    }

    void Interpreter::executePrint(const PrintStmt* stmt) {
        if (!stmt) return;
        std::cout << "Print Output: " << stmt->expression << std::endl;
    }
}