#ifndef AEGIS_AST_NODES_HPP
#define AEGIS_AST_NODES_HPP

#include <string>
#include <vector>
#include <memory>
#include <utility> // std::move のために追加
#include "../token.hpp"

namespace aegis {

    class Stmt {
    public:
        // デストラクタを正しく定義
        virtual ~Stmt() = default;

        virtual void anchor() const {}
    };

    class PrintStmt : public Stmt {
    public:
        std::string expression;
        PrintStmt(std::string expr) : expression(std::move(expr)) {}
    };

    class FunctionStmt : public Stmt {
    public:
        Token name;
        std::vector<std::unique_ptr<Stmt>> body;
        FunctionStmt(Token name, std::vector<std::unique_ptr<Stmt>> body)
            : name(std::move(name)), body(std::move(body)) {}
    };

}
#endif