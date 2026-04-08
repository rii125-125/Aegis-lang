#ifndef AEGIS_INTERPRETER_HPP
#define AEGIS_INTERPRETER_HPP

#include "../syntax/ast_nodes.hpp"
#include <vector>
#include <memory>

namespace aegis {
    class Interpreter {
        public:
            void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);

        private:
            void execute(const Stmt* stmt);
            void executePrint(const PrintStmt* stmt);
            void executeFunction(const FunctionStmt* stmt);
    };
}

#endif